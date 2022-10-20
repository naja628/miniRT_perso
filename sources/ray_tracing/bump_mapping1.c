#include "mlx.h" // ok because -I sources/mlx_linux should find it
#include <stdlib.h>
#include "vec.h"
#include "utypes.h"
#include "bump_mapping.h"

// This line bad because gets mlx from system instead of our repo
// # include <mlx.h>
// Are these really needed? 
// # include <sys/mman.h>
// # include <X11/Xlib.h>
// # include <X11/Xutil.h>
// # include <sys/ipc.h>
// # include <sys/shm.h>
// # include <X11/extensions/XShm.h>
// # include <X11/XKBlib.h>

#define E_LOADING 1
#define E_NOT32 2
// make imdata struct from xpm image (given by filename)
// possible errors (returns)
// 1 : error loading file
// 2 : native encoding of color is not 32 bits
// this makes the data unreadable (write-only) using only mlx_functions
// so we can't do bump_mapping
int	ft_xpm_to_imdata(void *mlx, char *filename, t_imdata *buff)
{
	void	*img;
	int		bitspp;
	int		b;
	int		c;

	img = mlx_xpm_file_to_image(mlx, filename, &buff->w, &buff->h);
	if (!img)
		return (E_LOADING);
	buff->data = mlx_get_data_addr(img, &bitspp, &b, &c);
	mlx_destroy_image(mlx, img);
	if (bitspp != 32)
	{
		// TODO maybe print warning
		return (E_NOT32);
	}
	else
		return (0);
}

int	ft_xpm_to_normals(void *mlx, t_normals *map, char *fn, float maxh)
{
	t_imdata	imdata;
	int			errcode;

	errcode = ft_xpm_to_imdata(mlx, fn, &imdata);
	if (errcode == 0)
		ft_mk_normal_map(map, &imdata, maxh);
	else
		map->data = NULL;
	return (errcode);
}

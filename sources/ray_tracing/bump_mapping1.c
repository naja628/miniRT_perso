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

// make imdata struct from xpm image (given by filename)
// possible errors (returns)
// 1 : error loading file
// 2 : native encoding of color is not 32 bits
// this makes the data unreadable (write-only) using only mlx_functions
// so we can't do bump_mapping
#include <stdio.h>
int	ft_xpm_to_imdata(void *mlx, char *filename, t_imdata *buff, void **delendum)
{
	void	*img;
	int		bitspp;
	int		b;
	int		c;

	img = mlx_xpm_file_to_image(mlx, filename, &buff->w, &buff->h);
	if (!img)
		return (E_LOADING);
	buff->data = mlx_get_data_addr(img, &bitspp, &b, &c);
	*delendum = img;
// 	mlx_destroy_image(mlx, img);
	if (bitspp != 32)
		return (E_NOT32);
	return (0);
}

int	ft_xpm_to_normals(void *mlx, t_normals *map, char *fn, float maxh)
{
	t_imdata	imdata;
	int			errcode;
	void 		*img_to_del;

	errcode = ft_xpm_to_imdata(mlx, fn, &imdata, &img_to_del);
	if (errcode == 0)
		ft_mk_normal_map(map, &imdata, maxh);
	else
		map->data = NULL;
	mlx_destroy_image(mlx, img_to_del);
	return (errcode);
}

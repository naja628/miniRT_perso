#include "scr.h"
#include "mlx.h" // ok because -I sources/mlx_linux should find it

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

void	ft_init_scr(t_scr *t, t_uint w, t_uint h, char *winname)
{
	t->mlx = mlx_init();
	t->win = mlx_new_window(t->mlx, w, h, winname);
	t->imptr = mlx_new_image(t->mlx, w, h);
	t->w = w;
	t->h = h;
	t->data = mlx_get_data_addr(t->imptr, &t->bits, &t->line_sz, &t->bigend);
}

void	ft_pixel_to_scr(t_scr *scr, int x, int y, int rgb)
{
	t_uint	*data;
	t_uint	native_rgb;
	char	*write_addr;
	int		cur_byte;

	data = (t_uint *) scr->data;
	if (scr->bits == 32)
	{
		native_rgb = mlx_get_color_value(scr->mlx, rgb);
		data[x + y * scr->line_sz / sizeof(t_uint)] = native_rgb;
		return ;
	}
	cur_byte = 0;
	write_addr = scr->data + y * scr->line_sz + x * (scr->bits / 8);
	while (cur_byte < (scr->bits / 8))
	{
		if (scr->bigend)
			write_addr[cur_byte] = native_rgb >> 8
				* (4 - (scr->bits / 8) + cur_byte);
		else
			write_addr[cur_byte] = native_rgb >> 8 * cur_byte;
		++cur_byte;
	}
}

#include "mlx.h" // ok because -I sources/mlx_linux should find it
#include <stdlib.h>
#include "vec.h"
#include "utypes.h"
#include "bump_mapping.h"

#include <stdio.h>
static float	ft_hdiff(t_uint from, t_uint to, float max_height)
{
	int	diff;

	// (TODO think)
	// I think doing this way is ok regardless of endianness
	// but it kinda depends if blue is always the least
	// significant bits or if the X-server encoding
	// endianness is independant from the machines 
	// may use (green or red) to be safer
	// (they are supposed to be the same and green will become 
	// red when endianness changes)
	from = 0xff & from;
	to = 0xff & to;
	diff = to - from;
// 	printf("%f\n", max_height);
// 	printf("diff %f\n", (float) diff / 255);
	return ((float) diff * max_height / 255);
}

static t_uint	ft_atxy(int x, int y, t_imdata *data)
{
	t_uint	*cast;

	cast = (t_uint *) data->data;
// 	printf("at %d %d : %x\n", x, y, cast[(x % data->w) + (y % data->h) * data->w]);
	return (cast[(x % data->w) + (y % data->h) * data->w]);
}

static void	ft_init_map(t_normals *map, t_imdata *h)
{
	map->w = h->w;
	map->h = h->h;
	map->data = malloc(sizeof(t_vec) * h->w * h->h);
}

#include <stdio.h>
#include "debug.h"
void	ft_mk_normal_map(t_normals *map, t_imdata *h, float maxh)
{
	int		x;
	int		y;
	t_vec	bl_tr;
	t_vec	tl_br;
	float	hdiff;

	ft_init_map(map, h);
	maxh *= map->h;
// 	printf("maxh %f\n");
// 	printf("%p mk normal %d %d %p\n", map, map->h, map->w, map->data);
	if (!map->data)
		return ;
	y = 0;
	while (y < h->h)
	{
		x = 0;
		while (x < h->w)
		{
			hdiff = ft_hdiff(ft_atxy(x, y + 1, h), ft_atxy(x + 1, y, h), maxh);
			bl_tr = ft_vec(1, 1, hdiff);
			hdiff = ft_hdiff(ft_atxy(x, y, h), ft_atxy(x + 1, y + 1, h), maxh);
			tl_br = ft_vec(1, -1, hdiff);
			map->data[x + (map->h - y - 1) * map->w] = ft_cross(tl_br, bl_tr);
			ft_make_unit(map->data + x++ + (map->h - y - 1) * map->w);
		}
		++y;
	}
	printf("normal map done\n");
}

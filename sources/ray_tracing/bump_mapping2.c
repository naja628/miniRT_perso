/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:12 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:42:56 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h" // ok because -I sources/mlx_linux should find it
#include <stdlib.h>
#include "vec.h"
#include "utypes.h"
#include "bump_mapping.h"

static float	ft_hdiff(t_uint from, t_uint to, float max_height)
{
	int	diff;

	from = 0xff & from;
	to = 0xff & to;
	diff = to - from;
	return ((float) diff * max_height / 255);
}

static t_uint	ft_atxy(int x, int y, t_imdata *data)
{
	t_uint	*cast;

	cast = (t_uint *) data->data;
	return (cast[(x % data->w) + (y % data->h) * data->w]);
}

static void	ft_init_map(t_normals *map, t_imdata *h)
{
	map->w = h->w;
	map->h = h->h;
	map->data = malloc(sizeof(t_vec) * h->w * h->h);
}

void	ft_mk_normal_map(t_normals *map, t_imdata *h, float maxh)
{
	int		x;
	int		y;
	t_vec	bl_tr;
	t_vec	tl_br;
	float	hdiff;

	ft_init_map(map, h);
	maxh *= map->h;
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
}

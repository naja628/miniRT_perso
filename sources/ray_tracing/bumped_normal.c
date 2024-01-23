/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumped_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:13 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:13 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "shape.h"
#include "vec.h"
#include "bases.h"
#include "bump_mapping.h"

static t_vec	ft_get_perturb(t_vec2 xy, float map_height, t_normals *bumps)
{
	int	x;
	int	y;

	xy.x = ft_fmod(xy.x, map_height);
	xy.y = ft_fmod(xy.y, map_height);
	x = (int) floor(xy.x / map_height * bumps->w);
	y = (int) floor(xy.y / map_height * bumps->h);
	x %= bumps->w;
	y %= bumps->h;
	return (bumps->data[x + y * bumps->w]);
}

t_vec	ft_bumped_normal(t_vec p, t_shape *s)
{
	t_vec	normal;
	t_vec2	xy;
	t_basis	basis;
	float	yh_cone;
	t_sp_cn	poly;

	if (!s->bump_map)
		return (ft_normal(p, s));
	xy = ft_map2d(p, s, &basis);
	normal = ft_get_perturb(xy, s->map_height, s->bump_map);
	if (s->type == SHP_SPHERE && (xy.x == 0))
	{
		poly.sp = s->data;
		normal.x /= sin(xy.y / poly.sp->radius);
		ft_make_unit(&normal);
	}
	if (s->type == SHP_CYLIN && !(ft_near_zero(xy.y, 0.001)))
	{
		poly.cn = s->data;
		yh_cone = ft_dot(ft_diff(p, poly.cn->p), poly.cn->dir);
		normal.x /= poly.cn->slope * yh_cone;
		ft_make_unit(&normal);
	}
	return (ft_in_basis(&basis, normal));
}

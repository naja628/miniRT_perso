/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:18 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:18 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "math_utils.h"
#include "vec.h"
#include "line.h"
#include "shape.h"
#include "bases.h"

static float	ft_hyp(float slope)
{
	return (sqrt(1 + slope * slope));
}

int	ft_cn_inter(float *t, t_line *ray, void *cn_data)
{
	t_cone		*cn;
	t_cncomp	cp;
	int			i;
	float		ts[2];
	float		sqsl;

	cn = (t_cone *) cn_data;
	ft_para_perp(cn->dir, ft_diff(ray->p, cn->p), &(cp.ppara), &(cp.pperp));
	ft_para_perp(cn->dir, ray->dir, &(cp.dpara), &(cp.dperp));
	sqsl = cn->slope * cn->slope;
	cp.a = ft_sqnorm(cp.dperp) - sqsl * ft_sqnorm(cp.dpara);
	cp.b = ft_dot(cp.dperp, cp.pperp) - sqsl * ft_dot(cp.ppara, cp.dpara);
	cp.b *= 2;
	cp.c = ft_sqnorm(cp.pperp) - sqsl * ft_sqnorm(cp.ppara);
	if (ft_near_zero(cp.a, 0.001) || !ft_roots(ts, cp.b / cp.a, cp.c / cp.a))
		return (0);
	i = 0;
	while (i < 2)
	{
		*t = ts[i++];
		cp.height = ft_dot(cn->dir, ft_diff(ft_point_at_t(ray, *t), cn->p));
		if (*t >= 0 && 0 <= cp.height && cp.height <= cn->h)
			return (1);
	}
	return (0);
}

t_vec	ft_cn_normal(t_vec p, void *cn_data)
{
	t_cone	*cn;
	t_vec	normal;
	t_vec	para;
	float	height;
	float	hyp;

	cn = (t_cone *) cn_data;
	ft_para_perp(cn->dir, ft_diff(p, cn->p), &para, &normal);
	height = ft_dot(cn->dir, para);
	hyp = ft_hyp(cn->slope);
	ft_scale(1.0 / (height * cn->slope * hyp), &normal);
	ft_add_to(&normal, ft_scaled(-(cn->slope / hyp), cn->dir));
	return (normal);
}

static void	ft_cn_basis(t_vec p, void *cn_data, t_basis *basis)
{
	t_cone	*cn;
	t_vec	normal;
	t_vec	neg_y_dir;

	cn = (t_cone *) cn_data;
	normal = ft_cn_normal(p, cn_data);
	neg_y_dir = ft_scaled(-1, ft_diff(p, cn->p));
	ft_make_unit(&neg_y_dir);
	ft_complete_basis2(normal, neg_y_dir, basis);
}

// y goes to height, x goes to angle times radius
t_vec2	ft_cn_map(t_vec p, void *cn_data, t_basis *basis)
{
	t_cone		*cn;
	t_vec2		xy;
	t_vec		para;
	t_vec		perp;
	t_vec		angle_zero;

	cn = (t_cone *) cn_data;
	ft_para_perp(cn->dir, ft_diff(p, cn->p), &para, &perp);
	xy.y = ft_hyp(cn->slope) * ft_dot(para, cn->dir);
	ft_make_unit(&perp);
	if (basis)
		ft_cn_basis(p, cn_data, basis);
	if (!ft_colin(cn->dir, ft_vec(1, 0, 0)))
		angle_zero = ft_cross(ft_vec(1, 0, 0), cn->dir);
	else
		angle_zero = ft_cross(cn->dir, ft_vec(0, 0, 1));
	ft_make_unit(&angle_zero);
	xy.x = ft_angle(angle_zero, perp);
	if (ft_dot(ft_cross(angle_zero, perp), cn->dir) < 0)
		xy.x = 2 * M_PI - xy.x;
	return (xy);
}

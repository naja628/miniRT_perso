/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
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

int	ft_cy_inter(float *t, t_line *ray, void *cy_data)
{
	t_cylinder	*cy;
	t_cycomp	cp;
	int			i;
	float		ts[2];

	cy = (t_cylinder *) cy_data;
	ft_para_perp(cy->dir, ft_diff(ray->p, cy->p), &(cp.ppara), &(cp.pperp));
	ft_para_perp(cy->dir, ray->dir, &(cp.dpara), &(cp.dperp));
	cp.a = ft_sqnorm(cp.dperp);
	cp.b = 2 * ft_dot(cp.pperp, cp.dperp);
	cp.c = ft_sqnorm(cp.pperp) - cy->r * cy->r;
	if (ft_near_zero(cp.a, 0.001) || !ft_roots(ts, cp.b / cp.a, cp.c / cp.a))
		return (0);
	i = 0;
	while (i < 2)
	{
		*t = ts[i];
		cp.height = ft_dot(cy->dir, ft_diff(ft_point_at_t(ray, *t), cy->p));
		if (*t >= 0 && 0 <= cp.height && cp.height <= cy->h)
			return (1);
		++i;
	}
	return (0);
}

t_vec	ft_cy_normal(t_vec p, void *cy_data)
{
	t_cylinder	*cy;
	t_vec		normal;

	cy = (t_cylinder *) cy_data;
	ft_para_perp(cy->dir, ft_diff(p, cy->p), NULL, &normal);
	ft_scale(1.0 / cy->r, &normal);
	return (normal);
}

// y goes to height, x goes to angle times radius
t_vec2	ft_cy_map(t_vec p, void *cy_data, t_basis *basis)
{
	t_cylinder	*cy;
	t_vec2		xy;
	t_vec		para;
	t_vec		perp;
	t_vec		angle_zero;

	cy = (t_cylinder *) cy_data;
	ft_para_perp(cy->dir, ft_diff(p, cy->p), &para, &perp);
	xy.y = ft_dot(para, cy->dir);
	ft_scale(1.0 / cy->r, &perp);
	if (basis)
		ft_complete_basis2(perp, ft_scaled(-1, cy->dir), basis);
	if (!ft_colin(cy->dir, ft_vec(1, 0, 0)))
		angle_zero = ft_cross(ft_vec(1, 0, 0), cy->dir);
	else
		angle_zero = ft_cross(cy->dir, ft_vec(0, 0, 1));
	ft_make_unit(&angle_zero);
	xy.x = ft_angle(angle_zero, perp);
	if (ft_dot(ft_cross(angle_zero, perp), cy->dir) < 0)
		xy.x = 2 * M_PI - xy.x;
	xy.x *= cy->r;
	return (xy);
}

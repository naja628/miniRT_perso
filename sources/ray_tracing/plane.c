/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:26 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:26 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_utils.h"
#include "vec.h"
#include "line.h"
#include "shape.h"
#include "bases.h"

// <p + td, n > = 0 (when <d, n> /= 0)
// <=> t = -<p,n> / <d,n>
// in code below a = <p,n>, b = <d,n>
int	ft_pl_inter(float *t, t_line *ray, void *pl_data)
{
	const float	eps = 0.01;
	float		a;
	float		b;
	t_plane		*pl;

	pl = (t_plane *) pl_data;
	b = ft_dot(ray->dir, pl->dir);
	a = ft_dot(ft_diff(ray->p, pl->p), pl->dir);
	if (fabs(b) < eps)
		return (0);
	*t = -a / b;
	if (*t > 0)
		return (1);
	else
		return (0);
}

t_vec	ft_pl_normal(t_vec p, void *pl_data)
{
	(void) p;
	return (((t_plane *) pl_data)->dir);
}

t_vec2	ft_pl_map(t_vec p, void *pl_data, t_basis *basis)
{
	t_vec		u;
	t_vec		v;
	t_vec2		xy;
	t_plane		*pl;

	pl = (t_plane *) pl_data;
	if (ft_colin(pl->dir, ft_vec(0, 0, 1)))
		ft_complete_basis(pl->dir, ft_vec(0, -1, 0), &u, &v);
	else
		ft_complete_basis(pl->dir, ft_vec(0, 0, -1), &u, &v);
	xy.x = ft_dot(p, u);
	xy.y = ft_dot(p, v);
	if (basis)
		ft_set_basis(basis, u, v, pl->dir);
	return (xy);
}

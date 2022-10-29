/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:37 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:37 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

// vec3.c scaling and norms/lengths

float	ft_sqnorm(t_vec u)
{
	return (u.x * u.x + u.y * u.y + u.z * u.z);
}

float	ft_norm(t_vec u)
{
	return (sqrt(ft_sqnorm(u)));
}

void	ft_scale(float lambda, t_vec *u)
{
	u->x *= lambda;
	u->y *= lambda;
	u->z *= lambda;
}

t_vec	ft_scaled(float lambda, t_vec u)
{
	t_vec	v;

	v = u;
	ft_scale(lambda, &v);
	return (v);
}

void	ft_make_unit(t_vec *u)
{
	ft_scale(1 / ft_norm(*u), u);
}

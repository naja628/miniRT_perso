/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:36 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:36 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

// vec2.c products
t_vec	ft_cross(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.y * v.z - v.y * u.z;
	w.y = u.z * v.x - v.z * u.x;
	w.z = u.x * v.y - v.x * u.y;
	return (w);
}

float	ft_dot(t_vec u, t_vec v)
{
	float	res;

	res = u.x * v.x;
	res += u.y * v.y;
	res += u.z * v.z;
	return (res);
}

t_vec	ft_vec_mult(t_vec u, t_vec v)
{
	t_vec	w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}

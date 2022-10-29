/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:24 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:24 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_utils.h"

float	ft_fmod(float q, float d)
{
	float	ret;

	ret = fmod(q, d);
	if (ret < 0)
		ret += fabs(d);
	return (ret);
}

int	ft_near_zero(float x, float eps)
{
	return (-eps < x && x < eps);
}

// test if 2 *unit* vectors are (almost bc floats) colinear
int	ft_colin(t_vec u, t_vec v)
{
	const float	eps = 0.0001;
	float		cos;

	cos = ft_dot(u, v);
	if (1 - cos * cos < eps)
		return (1);
	else
		return (0);
}

// compute the absolute angle in [0, pi] between u and v
float	ft_angle(t_vec u, t_vec v)
{
	float	cos;

	cos = ft_dot(u, v);
	if (cos > 1)
		return (0);
	else if (cos < -1)
		return (M_PI);
	else
		return (acos(cos));
}

// idea : find (real) roots of the polynomial t^2 + b.t + c
// note : for a.t^2 + b.t + c provide b/a and c/a as args
//
// how it actually works :
// returns 0 if there are no roots
// 1 otherwise
// t shall be a length 2 float array 
// and will be filled with the roots (in increasing order)
// before returning.
// note : if the determinant is 0, the 2 roots will be the same
int	ft_roots(float *t, float b, float c)
{
	float	discr;

	discr = b * b - 4 * c;
	if (discr < 0)
		return (0);
	discr = sqrt(discr);
	t[0] = (-b - discr) / 2;
	t[1] = (-b + discr) / 2;
	return (1);
}

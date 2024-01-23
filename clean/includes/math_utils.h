/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:35:51 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:35:51 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "vec.h"

// fmod but returns "right" answer for negative qs
float	ft_fmod(float q, float d);

int		ft_near_zero(float x, float eps);

// compute the absolute angle in [0, pi] between u and v
float	ft_angle(t_vec u, t_vec v);

// test if 2 *unit* vectors are (almost bc floats) colinear
int		ft_colin(t_vec u, t_vec v);

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
int		ft_roots(float *t, float b, float c);

// takes a *unit* vector 'dir'
// and a vector ('decomped') to be decomposed into
// parallel and perpendicular components (relative to 'dir')
// para and perp will point to the newly computed components after the call.
// para or perp can be provided as 'NULL' if you want a component to be ignored
void	ft_para_perp(t_vec dir, t_vec decomped, t_vec *para, t_vec *perp);

// fast exponentiaton (of float to an integer power)
float	ft_fastexp(float x, int pow);

// predicate:
// u, and v are in the same side of the plane passing through 0 with 
// normal n
int		ft_same_side(t_vec n, t_vec u, t_vec v);

#endif

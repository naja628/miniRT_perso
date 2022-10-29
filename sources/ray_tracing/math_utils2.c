/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:25 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:25 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

float	ft_fastexp(float x, int pow)
{
	if (pow == 0)
		return (1);
	if (pow % 2 == 1)
		return (x * ft_fastexp(x * x, pow / 2));
	else
		return (ft_fastexp(x * x, pow / 2));
}

// takes a *unit* vector 'dir'
// and a vector ('decomped') to be decomposed into
// parallel and perpendicular components (relative to 'dir')
// para and perp will point to the newly computed components after the call.
// para or perp can be provided as 'NULL' if you want a component to be ignored
void	ft_para_perp(t_vec dir, t_vec decomped, t_vec *para, t_vec *perp)
{
	t_vec	para_buff;
	t_vec	*para_addr;

	if (para)
		para_addr = para;
	else
		para_addr = &para_buff;
	*para_addr = ft_scaled(ft_dot(dir, decomped), dir);
	if (perp)
		*perp = ft_diff(decomped, *para_addr);
}

int	ft_same_side(t_vec n, t_vec u, t_vec v)
{
	return (ft_dot(n, u) * ft_dot(v, u) > 0);
}


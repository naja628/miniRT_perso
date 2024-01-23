/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:01:37 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 23:02:09 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	want_positive(float x, int *berr)
{
	if (*berr)
		return (*berr);
	if (x < 0.01)
		*berr = WRONG_VALUE;
	return (*berr);
}

int	want_ratio(float ratio, int *berr)
{
	if (*berr)
		return (*berr);
	if (!(0.0 <= ratio && ratio <= 1.0))
		*berr = WRONG_VALUE;
	return (*berr);
}

int	want_unit(t_vec	unit, int *berr)
{
	if (*berr)
		return (*berr);
	if (!ft_near_zero(ft_norm(unit) - 1, 0.005))
		*berr = DIR_NOT_UNIT;
	return (*berr);
}

int	set_if_zero(int *berr, int new_err)
{
	if (*berr)
		return (*berr);
	*berr = new_err;
	return (*berr);
}

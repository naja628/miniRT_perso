/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:01:56 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 23:02:17 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	want_coefs(t_shape *s, int *berr)
{
	if (*berr)
		return (*berr);
	if (s->dif_coef < 0 || s->spec_coef < 0 || s->refl_coef < 0
		|| s->dif_coef + s->spec_coef + s->refl_coef > 1.01)
		*berr = WRONG_VALUE;
	return (*berr);
}

int	want_bool(int boolean, int *berr)
{
	if (*berr)
		return (*berr);
	if (!(boolean == 0 || boolean == 1))
		*berr = WRONG_VALUE;
	return (*berr);
}

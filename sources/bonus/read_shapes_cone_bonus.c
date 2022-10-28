/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shapes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 23:00:32 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 23:01:01 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*read_cone(char **line, int *ret)
{
	t_cone	*cn;

	if (*ret)
		return (NULL);
	cn = malloc(sizeof(t_cone));
	if (!cn)
	{
		*ret = MALLOC_ERR;
		return (NULL);
	}
	cn->p = read_vec(line, ret);
	*line = skip_spaces(*line);
	cn->dir = read_vec(line, ret);
	want_unit(cn->dir, ret);
	*line = skip_spaces(*line);
	cn->slope = ft_atof_minirt(line, ret);
	want_positive(cn->slope, ret);
	*line = skip_spaces(*line);
	cn->h = ft_atof_minirt(line, ret);
	want_positive(cn->h, ret);
	return ((t_cone *)cn);
}

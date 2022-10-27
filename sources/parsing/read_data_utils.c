/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:58:43 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 22:59:24 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	eol_checker(char **line)
{
	*line = skip_spaces(*line);
	if (*(*line) != '\n' && *(*line) != '\0')
		return (1);
	return (0);
}

static void	skip_comma(char **line, int *error)
{
	if (!(*error) && **line != ',')
		*error = COMMA_SEP;
	++(*line);
}

t_vec	read_vec(char **line, int *error)
{
	t_vec	vec;

	vec.x = ft_atof_minirt(line, error);
	skip_comma(line, error);
	vec.y = ft_atof_minirt(line, error);
	skip_comma(line, error);
	vec.z = ft_atof_minirt(line, error);
	return (vec);
}

t_vec	read_color(char **line, int *error)
{
	t_vec	color;

	if (*error)
		return (ft_vec(0, 0, 0));
	color.x = ft_atoi_minirt(line, error);
	skip_comma(line, error);
	color.y = ft_atoi_minirt(line, error);
	skip_comma(line, error);
	color.z = ft_atoi_minirt(line, error);
	ft_scale(1.0 / 255, &color);
	if (!((0 <= color.x && color.x <= 1)
			&& (0 <= color.y && color.y <= 1)
			&& (0 <= color.z && color.z <= 1)))
		set_if_zero(error, WRONG_VALUE);
	return (color);
}

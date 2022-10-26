/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:58:43 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/26 23:21:31 by xle-boul         ###   ########.fr       */
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

t_vec	read_vec(char **line, int *error)
{
	t_vec	vec;

	vec.x = ft_atof_minirt(line, error);
	if (**line != ',')
		*error = 1;
	++(*line);
	vec.y = ft_atof_minirt(line, error);
	if (**line != ',')
		*error = 1;
	++(*line);
	vec.z = ft_atof_minirt(line, error);
	return (vec);
}

t_vec	read_color(char **line, int *error)
{
	t_vec	color;
	int		debug;

	debug = ft_atoi_minirt(line, error);
	color.x = (float) debug / 255;
	if (**line != ',')
		*error = 1;
	++(*line);
	color.y = (float)ft_atoi_minirt(line, error) / 255;
	if (**line != ',')
		*error = 1;
	++(*line);
	color.z = (float)ft_atoi_minirt(line, error) / 255;
	if ((0 <= color.x && color.x <= 1)
		|| (0 <= color.y && color.y <= 1)
		|| (0 <= color.z && color.z <= 1))
		*error = 3;
	return (color);
}

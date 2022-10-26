/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:32:47 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/26 23:26:07 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// TODO pass error code to atoi and atof to prevent cases of error (no digit)

int	read_ambient_light(t_parse *intel, char *line)
{
	int	ret;

	ret = 0;
	line = skip_spaces(line);
	intel->scene.ambient = ft_atof_minirt(&line, &ret);
	line = skip_spaces(line);
	intel->scene.ambient_color = read_color(&line, &ret);
	if (eol_checker(&line) != 0)
		ret = TRAILING_CHARS;
	return (ret);
}

int	read_camera(t_parse *intel, char *line)
{
	int	ret;

	ret = 0;
	line = skip_spaces(line);
	intel->cam.viewpoint = read_vec(&line, &ret);
	line = skip_spaces(line);
	intel->cam.dir = read_vec(&line, &ret);
	if (!ft_near_zero(ft_sqnorm(intel->cam.dir) - 1, 0.01))
		ret = DIR_NOT_UNIT;
	line = skip_spaces(line);
	intel->cam.fov_deg = ft_atoi_minirt(&line, &ret);
	if (!(0 < intel->cam.fov_deg && intel->cam.fov_deg < 180))
		ret = WRONG_VALUE;
	if (eol_checker(&line) != 0)
		ret = TRAILING_CHARS;
	return (ret);
}

int	read_light(t_parse *intel, char *line)
{
	int	ret;
	t_light_list	*new;

	ret = 0;
	new = malloc(sizeof(t_light_list));
	if (!new)
		error_handler(MALLOC_ERR);
	new->next = intel->scene.lights;
	intel->scene.lights = new;
	new->light.no_flare = 0;
	line = skip_spaces(line);
	new->light.pos = read_vec(&line, &ret);
	line = skip_spaces(line);
	new->light.intensity = ft_atof_minirt(&line, &ret);
	if (0.0 <= new->light.intensity && new->light.intensity <= 1.0)
		ret = WRONG_VALUE;
	line = skip_spaces(line);
	new->light.color = read_color(&line, &ret);
	line = skip_spaces(line);
	new->light.no_flare = ft_atoi_minirt(&line, &ret);
	if (new->light.no_flare != 1 && new->light.no_flare != 0)
		ret = WRONG_VALUE;
	if (eol_checker(&line) != 0)
		ret = TRAILING_CHARS;
	return (ret);
}

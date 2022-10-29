/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:32:47 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 22:46:59 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	read_ambient_light(t_parse *intel, char *line)
{
	int	ret;

	ret = 0;
	line = skip_spaces(line);
	intel->scene.ambient = ft_atof_minirt(&line, &ret);
	want_ratio(intel->scene.ambient, &ret);
	line = skip_spaces(line);
	intel->scene.ambient_color = read_color(&line, &ret);
	if (eol_checker(&line) != 0)
		set_if_zero(&ret, TRAILING_CHARS);
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
	want_unit(intel->cam.dir, &ret);
	line = skip_spaces(line);
	intel->cam.fov_deg = ft_atoi_minirt(&line, &ret);
	if (!ret && !(0 < intel->cam.fov_deg && intel->cam.fov_deg < 180))
		set_if_zero(&ret, WRONG_VALUE);
	if (eol_checker(&line) != 0)
		set_if_zero(&ret, WRONG_VALUE);
	return (ret);
}

int	read_light(t_parse *intel, char *line)
{
	int				ret;
	t_light_list	*new;

	ret = 0;
	new = malloc(sizeof(t_light_list));
	if (!new)
		return (MALLOC_ERR);
	new->next = intel->scene.lights;
	intel->scene.lights = new;
	new->light.no_flare = 0;
	line = skip_spaces(line);
	new->light.pos = read_vec(&line, &ret);
	line = skip_spaces(line);
	new->light.intensity = ft_atof_minirt(&line, &ret);
	want_ratio(new->light.intensity, &ret);
	line = skip_spaces(line);
	new->light.color = read_color(&line, &ret);
	if (eol_checker(&line) == 0)
		return (ret);
	line = skip_spaces(line);
	new->light.no_flare = ft_atoi_minirt(&line, &ret);
	want_bool(new->light.no_flare, &ret);
	if (eol_checker(&line) != 0)
		set_if_zero(&ret, TRAILING_CHARS);
	return (ret);
}

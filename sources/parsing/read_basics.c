/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:32:47 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/25 22:32:12 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// TODO pass error code to atoi and atof to prevent cases of error (no digit)

void	read_ambient_light(t_parse *intel, char *line)
{
	line = skip_spaces(line);
	intel->scene.ambient = ft_atof_minirt(&line);
	line = skip_spaces(line);
	intel->scene.ambient_color = read_color(&line, &(intel->error));
	if (eol_checker(&line) != 0)
		intel->error = 2;
}

void	read_camera(t_parse *intel, char *line)
{
	line = skip_spaces(line);
	intel->cam.viewpoint = read_vec(&line, &(intel->error));
	line = skip_spaces(line);
	intel->cam.dir = read_vec(&line, &(intel->error));
	if (!ft_near_zero(ft_norm(intel->cam.dir) - 1, 0.01))
		intel->error = 4;
	line = skip_spaces(line);
	intel->cam.fov_deg = ft_atoi_minirt(&line);
	if (!(0 < intel->cam.fov_deg && intel->cam.fov_deg < 180))
		intel->error = 3;
	if (eol_checker(&line) != 0)
		intel->error = 2;
}

void	read_light(t_parse *intel, char *line)
{
	t_light_list	*new;

	new = malloc(sizeof(t_light_list));
	if (!new)
		error_handler(0);
	new->next = intel->scene.lights;
	intel->scene.lights = new;
	line = skip_spaces(line);
	new->light.pos = read_vec(&line, &(intel->error));
	line = skip_spaces(line);
	new->light.intensity = ft_atof_minirt(&line);
	if (0.0 <= new->light.intensity && new->light.intensity <= 1.0)
		intel->error = 3;
	line = skip_spaces(line);
	new->light.color = read_color(&line, &(intel->error));
	if (eol_checker(&line) != 0)
		intel->error = 2;
}

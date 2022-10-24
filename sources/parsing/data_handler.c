/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:03:04 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/20 19:08:16 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "debug.h"

// TODO copy line and send it to functions in order to check the end of the line
// after use: (line **)
// if (*line == '\n')
// intel->error = 2;

int	read_id(t_parse *intel)
{
	if (ft_strncmp(intel->line, AMBIENT_LIGHT, 1) == 0
		&& intel->line[1] == ' ')
		read_ambient_light(intel, (intel->line + 1));
	else if (ft_strncmp(intel->line, CAMERA, 1) == 0
		&& intel->line[1] == ' ')
		read_camera(intel, (intel->line + 1));
	else if (ft_strncmp(intel->line, LIGHT, 1) == 0
		&& intel->line[1] == ' ')
		read_light(intel, (intel->line + 1));
	else if (ft_strncmp(intel->line, SPHERE, 2) == 0
		&& intel->line[2] == ' ')
		read_shape(intel, (intel->line + 2), read_sphere, SHP_SPHERE);
	else if (ft_strncmp(intel->line, CYLINDER, 2) == 0
		&& intel->line[2] == ' ')
		read_shape(intel, (intel->line + 2), read_cylinder, SHP_CYLIN);
	else if (ft_strncmp(intel->line, PLANE, 2) == 0
		&& intel->line[2] == ' ')
		read_shape(intel, (intel->line + 2), read_plane, SHP_PLANE);
	else if (ft_strncmp(intel->line, CONE, 2) == 0
		&& intel->line[2] == ' ')
		read_shape(intel, (intel->line + 2), read_cone, SHP_CONE);
	else
		return (1);
	return (0);
}

// int main()
// {
// 	t_parse	intel;

// 	intel.line = "A 0.2 255,255,255\n";
// 	intel.error = 0;
// 	spot_first_element(&intel);
// 	print_vec("color", intel.scene.ambient_color);
// 	printf("%f %i", intel.scene.ambient, intel.error);
// 	return (0);
// }

// int	check_intel(t_parse *intel)
// {
// 	char	*ptr;

// 	while (*ptr != '\n' || *ptr != '\0')
// 	{
// 		spo
// 	}
// 	return (0);
// }
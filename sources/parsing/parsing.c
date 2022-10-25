/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:17:08 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/24 17:54:23 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "debug.h"

void	init_intel(t_parse *intel)
{
	intel->error = 0;
	intel->scene.lights = NULL;
	intel->scene.shapes = NULL;
}

void	read_intel(char *av, t_parse *intel)
{
	int		exit_code;

// 	init_intel(intel);
	exit_code = 0;
	intel->fd = open(av, O_RDONLY);
	if (intel->fd == -1)
		error_handler(2);
	while (19)
	{
		intel->line = get_next_line(intel->fd);
		if (!intel->line)
		{
			free(intel->line);
			break ;
		}
		exit_code = read_id(intel);
		free(intel->line);
		if (exit_code == 1)
			break ;
	}
	close(intel->fd);
	if (exit_code == 1)
		exit(EXIT_FAILURE);
	return (intel);
}

int	check_extension(char *file)
{
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL)
		return (1);
	if (file[ft_strlen(file) - 1] != 't' || file[ft_strlen(file) - 2] != 'r'
		|| file[ft_strlen(file) - 3] != '.')
		return (1);
	return (0);
}

void	print_all_data(t_parse intel)
{
	print_vec("cam viewpoint", intel.cam.viewpoint);
	print_vec("cam dir", intel.cam.dir);
	printf("cam fov %d\n", intel.cam.fov_deg);
	print_vec("light pos", intel.scene.lights->light.pos);
	print_vec("light color", intel.scene.lights->light.color);
	printf("light intensity %f\n", intel.scene.lights->light.intensity);
	printf("ambient %f\n", intel.scene.ambient);
	print_vec("ambient color", intel.scene.ambient_color);
	printf("shape type = %d\n", intel.scene.shapes->shape.type);
	print_vec("shape color", intel.scene.shapes->shape.color);
	printf("dif coef %f\n", intel.scene.shapes->shape.dif_coef);
	printf("spec coef %f\n", intel.scene.shapes->shape.spec_coef);
	printf("refl coef %f\n", intel.scene.shapes->shape.refl_coef);
	printf("map height %f\n", intel.scene.shapes->shape.map_height);
}


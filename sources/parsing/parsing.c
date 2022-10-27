/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:17:08 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/26 21:12:28 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "debug.h"

void	init_intel(t_parse *intel)
{
	intel->error = 0;
	intel->scene.lights = NULL;
	intel->scene.shapes = NULL;
	intel->num_ambients = 0;
	intel->num_cameras = 0;
}

int	cam_and_ambient_once(t_parse *intel, int *error)
{
	if (*error)
		return (*error);
	if (intel->num_cameras != 1)
		*error = NOT_ONE_CAM;
	if (intel->num_ambients != 1)
		*error = NOT_ONE_AMBIENT;
	print_error(*error, NULL);
	return (*error);
}

int	read_intel(char *av, t_parse *intel)
{
	int		error;

	error = 0;
	intel->fd = open(av, O_RDONLY);
	if (intel->fd == -1)
	{
		print_error(READ_FILE_ERR, NULL);
		return (READ_FILE_ERR);
	}
	while (19)
	{
		intel->line = get_next_line(intel->fd);
		if (!intel->line)
		{
			free(intel->line);
			break ;
		}
		error = read_id(intel);
		print_error(error, intel->line);
		free(intel->line);
		if (error)
			break ;
	}
	close(intel->fd);
	return (error || cam_and_ambient_once(intel, &error));
}

// We're not using this? maybe in main? TODO
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


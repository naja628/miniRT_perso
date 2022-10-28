/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:17:08 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/28 23:13:20 by xle-boul         ###   ########.fr       */
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

void	read_intel_loop(t_parse *intel, int *error)
{
	while (19)
	{
		intel->line = get_next_line(intel->fd);
		while (intel->line && intel->line[0] == '\n')
		{
			free(intel->line);
			intel->line = get_next_line(intel->fd);
		}
		if (!intel->line)
		{
			free(intel->line);
			break ;
		}
		*error = read_id(intel);
		print_error(*error, intel->line);
		free(intel->line);
		if (*error)
			break ;
	}
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
	read_intel_loop(intel, &error);
	close(intel->fd);
	return (error || cam_and_ambient_once(intel, &error));
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

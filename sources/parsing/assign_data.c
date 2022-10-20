/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:32:47 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/20 20:02:27 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	eol_checker(char *line)
{
	line = skip_spaces(line);
	// printf("last is %c$\nin %s\n", *line, line);
	if (*line != '\n' && *line != '\0')
		error_handler(3);
}

// TODO pass error code to atoi and atof to prevent cases of error (no digit)
t_vec	read_vec(char **line, int *error)
{
	t_vec	vec;

	vec.x = ft_atof_minirt(line);
	if (**line != ',')
		*error = 1;
	++(*line);
	vec.y = ft_atof_minirt(line);
	if (**line != ',')
		*error = 1;
	++(*line);
	vec.z = ft_atof_minirt(line);
	return (vec);
}

t_vec	read_color(char **line, int *error)
{
	t_vec	color;
	int		debug;

	debug = ft_atoi_minirt(line);
	color.x = (float) debug / 255;
	if (**line != ',')
		*error = 1;
	++(*line);
	color.y = (float)ft_atoi_minirt(line) / 255;
	if (**line != ',')
		*error = 1;
	++(*line);
	color.z = (float)ft_atoi_minirt(line) / 255;
	if ((0 <= color.x && color.x <= 1)
		|| (0 <= color.y && color.y <= 1)
		|| (0 <= color.z && color.z <= 1))
		*error = 3;
	return (color);
}

void	read_ambient_light(t_parse *intel, char *line)
{
	line = skip_spaces(line);
	intel->scene.ambient = ft_atof_minirt(&line);
	line = skip_spaces(line);
	intel->scene.ambient_color = read_color(&line, &(intel->error));
	printf("ambient\n");
	eol_checker(line);
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
	printf("cam\n");
	eol_checker(line);
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
	printf("light\n");
	eol_checker(line);
}

static void	default_shape(t_shape *shape)
{
	shape->is_checkered = 0;
	shape->dif_coef = 1;
	shape->spec_coef = 0;
	shape->refl_coef = 0;
	shape->bump_map = NULL;
	shape->map_height = 0;
}

void	read_shape(t_parse *intel, char *line, t_read fun, t_shapetype type)
{
	t_shape_list	*new;

	new = malloc(sizeof(t_shape_list));
	if (!new)
		error_handler(0);
	new->next = intel->scene.shapes;
	intel->scene.shapes = new;
	new->shape.type = type;
	line = skip_spaces(line);
	new->shape.data = fun(intel, &line);
	line = skip_spaces(line);
	new->shape.color = read_color(&line, &(intel->error));
	default_shape(&(new->shape));
	// read bonus
	printf("shape\n");
	eol_checker(line);
}

void	*read_sphere(t_parse *intel, char **line)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		error_handler(0);
	sp->center = read_vec(line, &(intel->error));
	*line = skip_spaces(*line);
	sp->radius = ft_atof_minirt(line) / 2;
	if (sp->radius < 0.01)
		intel->error = 3;
	return ((t_sphere *)sp);
}

void	*read_cylinder(t_parse *intel, char **line)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		error_handler(0);
	cy->p = read_vec(line, &(intel->error));
	*line = skip_spaces(*line);
	cy->dir = read_vec(line, &(intel->error));
	*line = skip_spaces(*line);
	cy->r = ft_atof_minirt(line) / 2;
	if (cy->r < 0.01)
		intel->error = 3;
	*line = skip_spaces(*line);
	cy->h = ft_atof_minirt(line);
	return ((t_cylinder *)cy);
}

void	*read_plane(t_parse *intel, char **line)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		error_handler(0);
	pl->p = read_vec(line, &(intel->error));
	*line = skip_spaces(*line);
	pl->dir = read_vec(line, &(intel->error));
	return ((t_plane *)pl);
}

void	*read_cone(t_parse *intel, char **line)
{
	t_cone	*cn;

	cn = malloc(sizeof(t_cone));
	if (!cn)
		error_handler(0);
	cn->p = read_vec(line, &(intel->error));
	*line = skip_spaces(*line);
	cn->dir = read_vec(line, &(intel->error));
	*line = skip_spaces(*line);
	cn->slope = ft_atof_minirt(line);
	*line = skip_spaces(*line);
	cn->h = ft_atof_minirt(line);
	return ((t_cone *)cn);
}

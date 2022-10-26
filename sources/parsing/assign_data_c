/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:32:47 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/24 18:21:24 by xle-boul         ###   ########.fr       */
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

char	*copy_xpm(char **line, int len)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = malloc(sizeof(char) * len + 1);
	if (!file_name)
		error_handler(0);
	while (i < len)
	{
		file_name[i] = *(*line);
		(*line)++;
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}

int	file_name_length(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != ' ' && line[1] != '\n' && line[1] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	check_xpm(char *file_name)
{
	if (ft_strnstr(file_name, ".xpm", ft_strlen(file_name)) == NULL)
		return (1);
	if (file_name[ft_strlen(file_name) - 1] != 'm'
		|| file_name[ft_strlen(file_name) - 2] != 'p'
		|| file_name[ft_strlen(file_name) - 3] != 'x'
		|| file_name[ft_strlen(file_name) - 4] != '.')
		return (1);
	return (0);
}

int	read_bonus(char *line, t_shape_list *new, void *mlx)
{
	char		*file_name;
	t_normals	*map;

	line = skip_spaces(line);
	new->shape.dif_coef = ft_atof_minirt(&line);
	printf("shape %f\n", new->shape.dif_coef);
	line = skip_spaces(line);
	new->shape.spec_coef = ft_atof_minirt(&line);
	line = skip_spaces(line);
	new->shape.refl_coef = ft_atof_minirt(&line);
	line = skip_spaces(line);
	new->shape.is_checkered = ft_atoi_minirt(&line);
	if (eol_checker(&line) == 0)
		return (0);
	printf("rb0\n");
	map = malloc(sizeof(t_normals));
	if (!map)
		error_handler(0);
	printf("map %p\n", map);
	file_name = copy_xpm(&line, file_name_length(line));
	printf("file name = _%s_\n", file_name);
	line = skip_spaces(line);
	new->shape.map_height = ft_atof_minirt(&line);
	if (check_xpm(file_name) == 0)
	{
		printf("rb1\n");
		// printf("scanned correctly\n");
		printf("err %d", ft_xpm_to_normals(mlx, map, file_name, 0.05));
		new->shape.bump_map = map;
		printf("rb2\n");
	}
	free(file_name);
	//mlx has to arrive here ^
	return (0);
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
	if (eol_checker(&line) != 0)
		error_handler(3);
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
		error_handler(3);
}

void	read_light(t_parse *intel, char *line)
{
	t_light_list	*new;

	new = malloc(sizeof(t_light_list));
	if (!new)
		error_handler(0);
	new->next = intel->scene.lights;
	intel->scene.lights = new;
	new->light.no_flare = 0;
	line = skip_spaces(line);
	new->light.pos = read_vec(&line, &(intel->error));
	line = skip_spaces(line);
	new->light.intensity = ft_atof_minirt(&line);
	if (0.0 <= new->light.intensity && new->light.intensity <= 1.0)
		intel->error = 3;
	line = skip_spaces(line);
	new->light.color = read_color(&line, &(intel->error));
	line = skip_spaces(line);
	new->light.no_flare = ft_atoi_minirt(&line);
	if (new->light.no_flare != 1 && new->light.no_flare != 0)
		intel->error = 3;
	if (eol_checker(&line) != 0)
		error_handler(3);
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
	if (eol_checker(&line) != 0)
		read_bonus(line, new, intel->mlx);
	if (eol_checker(&line) != 0)
		printf("wtf\n");
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

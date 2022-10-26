/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:30:23 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/26 23:27:58 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	default_shape(t_shape *shape)
{
	shape->is_checkered = 0;
	shape->dif_coef = 1;
	shape->spec_coef = 0;
	shape->refl_coef = 0;
	shape->bump_map = NULL;
	shape->map_height = 0;
}

int	read_shape(t_parse *intel, char *line, t_read fun, t_shapetype type)
{
	int				ret;
	t_shape_list	*new;

	ret = 0;
	new = malloc(sizeof(t_shape_list));
	if (!new)
		error_handler(MALLOC_ERR);
	new->next = intel->scene.shapes;
	intel->scene.shapes = new;
	new->shape.type = type;
	line = skip_spaces(line);
	new->shape.data = fun(intel, &line, &ret);
	line = skip_spaces(line);
	new->shape.color = read_color(&line, &ret);
	default_shape(&(new->shape));
	if (eol_checker(&line) != 0)
		read_bonus(line, new, intel->mlx, &ret);
	if (eol_checker(&line) != 0)
		ret = TRAILING_CHARS;
	return (ret);
}

void	*read_sphere(t_parse *intel, char **line, int *ret)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		error_handler(MALLOC_ERR);
	sp->center = read_vec(line, ret);
	*line = skip_spaces(*line);
	sp->radius = ft_atof_minirt(line, ret) / 2;
	if (sp->radius < 0.01)
		intel->error = 3;
	return ((t_sphere *)sp);
}

void	*read_cylinder(t_parse *intel, char **line, int *ret)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		error_handler(MALLOC_ERR);
	cy->p = read_vec(line, ret);
	*line = skip_spaces(*line);
	cy->dir = read_vec(line, ret);
	*line = skip_spaces(*line);
	cy->r = ft_atof_minirt(line, ret) / 2;
	if (cy->r < 0.01)
		intel->error = 3;
	*line = skip_spaces(*line);
	cy->h = ft_atof_minirt(line, ret);
	return ((t_cylinder *)cy);
}

void	*read_plane(t_parse *intel, char **line, int *ret)
{
	t_plane	*pl;

	(void)intel;
	pl = malloc(sizeof(t_plane));
	if (!pl)
		error_handler(MALLOC_ERR);
	pl->p = read_vec(line, ret);
	*line = skip_spaces(*line);
	pl->dir = read_vec(line, ret);
	return ((t_plane *)pl);
}

void	*read_cone(t_parse *intel, char **line, int *ret)
{
	t_cone	*cn;

	(void)intel;
	cn = malloc(sizeof(t_cone));
	if (!cn)
		error_handler(MALLOC_ERR);
	cn->p = read_vec(line, ret);
	*line = skip_spaces(*line);
	cn->dir = read_vec(line, ret);
	*line = skip_spaces(*line);
	cn->slope = ft_atof_minirt(line, ret);
	*line = skip_spaces(*line);
	cn->h = ft_atof_minirt(line, ret);
	return ((t_cone *)cn);
}

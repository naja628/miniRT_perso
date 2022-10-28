/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:30:23 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 23:04:39 by xle-boul         ###   ########.fr       */
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
		return (MALLOC_ERR);
	new->next = intel->scene.shapes;
	intel->scene.shapes = new;
	default_shape(&(new->shape));
	new->shape.type = type;
	line = skip_spaces(line);
	new->shape.data = fun(&line, &ret);
	line = skip_spaces(line);
	new->shape.color = read_color(&line, &ret);
	if (eol_checker(&line) != 0)
		return (read_bonus(line, new, intel->mlx, &ret));
	return (ret);
}

void	*read_sphere(char **line, int *ret)
{
	t_sphere	*sp;

	if (*ret)
		return (NULL);
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		*ret = MALLOC_ERR;
		return (NULL);
	}
	sp->center = read_vec(line, ret);
	*line = skip_spaces(*line);
	sp->radius = ft_atof_minirt(line, ret) / 2;
	want_positive(sp->radius, ret);
	return ((t_sphere *)sp);
}

void	*read_cylinder(char **line, int *ret)
{
	t_cylinder	*cy;

	if (*ret)
		return (NULL);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
	{
		*ret = MALLOC_ERR;
		return (NULL);
	}
	cy->p = read_vec(line, ret);
	*line = skip_spaces(*line);
	cy->dir = read_vec(line, ret);
	want_unit(cy->dir, ret);
	*line = skip_spaces(*line);
	cy->r = ft_atof_minirt(line, ret) / 2;
	want_positive(cy->r, ret);
	*line = skip_spaces(*line);
	cy->h = ft_atof_minirt(line, ret);
	want_positive(cy->h, ret);
	return ((t_cylinder *)cy);
}

void	*read_plane(char **line, int *ret)
{
	t_plane	*pl;

	if (*ret)
		return (NULL);
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		*ret = MALLOC_ERR;
		return (NULL);
	}
	pl->p = read_vec(line, ret);
	*line = skip_spaces(*line);
	pl->dir = read_vec(line, ret);
	want_unit(pl->dir, ret);
	return ((t_plane *)pl);
}

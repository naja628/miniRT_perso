/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:28 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:44:37 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "shape.h"
#include "vec.h"
#include "utypes.h"
#include "render.h"
#include "math_utils.h"

t_vec	ft_reflect(t_vec incident, t_vec normal)
{
	t_vec	reflected;

	reflected = ft_scaled(-2 * ft_dot(normal, incident), normal);
	ft_add_to(&reflected, incident);
	return (reflected);
}

t_vec	ft_flare(t_hit *hit, t_line *ray, t_light *light)
{
	t_vec	to_light;
	float	cos;

	if (light->no_flare)
		return (ft_vec(0, 0, 0));
	to_light = ft_diff(light->pos, ray->p);
	if (!hit || (ft_sqnorm(to_light) < ft_sqnorm(ft_diff(hit->p, ray->p))))
	{
		ft_make_unit(&to_light);
		cos = ft_dot(ray->dir, to_light);
		if (cos > 0)
			return (ft_scaled(ft_fastexp(cos, 1024) * 1.25, light->color));
	}
	return (ft_vec(0, 0, 0));
}

int	ft_closest_hit(t_hit *hit, t_line *ray, t_shape_list *shapes)
{
	float			t;
	float			min_t;
	t_shape_list	*it;
	t_shape			*hit_shape;

	min_t = -1;
	it = shapes;
	while (it)
	{
		if (ft_intersect(&t, ray, &it->shape)
			&& (min_t < 0 || t < min_t))
		{
			min_t = t;
			hit_shape = &it->shape;
		}
		it = it->next;
	}
	if (min_t < 0)
		return (0);
	ft_make_hit(hit, hit_shape, ft_point_at_t(ray, min_t));
	return (1);
}

void	ft_make_hit(t_hit *hit, t_shape *shape, t_vec p)
{
	hit->p = p;
	hit->sh = shape;
	hit->n = ft_bumped_normal(p, shape);
}

int	ft_shadowed(t_hit *hit, t_line *ray, t_scene *scene, t_light *light)
{
	t_vec			true_n;
	t_shape_list	*it;
	t_line			shadow_ray;
	float			t;
	float			sq_dist;

	shadow_ray.dir = ft_diff(light->pos, hit->p);
	sq_dist = ft_sqnorm(shadow_ray.dir);
	ft_make_unit(&shadow_ray.dir);
	shadow_ray.p = ft_vec_add(hit->p, ft_scaled(0.01, shadow_ray.dir));
	true_n = ft_normal(hit->p, hit->sh);
	if ((ft_dot(hit->n, shadow_ray.dir) * ft_dot(hit->n, ray->dir) > 0)
		|| (ft_dot(true_n, shadow_ray.dir) * ft_dot(true_n, ray->dir) > 0))
		return (1);
	it = scene->shapes;
	while (it)
	{
		if (ft_intersect(&t, &shadow_ray, &it->shape) && t * t < sq_dist)
			return (1);
		it = it->next;
	}
	return (0);
}

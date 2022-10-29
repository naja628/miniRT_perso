/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:35:56 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:35:56 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "shape.h"

typedef struct s_shape_list
{
	t_shape				shape;
	struct s_shape_list	*next;
}	t_shape_list;

typedef struct s_light
{
	t_vec	pos;
	float	intensity;
	t_vec	color;
	int		no_flare;
}	t_light;

typedef struct s_light_list
{
	t_light				light;
	struct s_light_list	*next;
}	t_light_list;

typedef struct s_scene
{
	float			ambient;
	t_vec			ambient_color;
	t_light_list	*lights;
	t_shape_list	*shapes;
}	t_scene;

typedef struct s_hit
{
	t_vec	p;
	t_vec	n;
	t_shape	*sh;
}	t_hit;

// find color seen "through" view ray 'ray')
// bounces and thresh control number of reflections
t_vec	ft_ray_color(t_line *ray, t_scene *scene, int bounces, float thresh);

// components (all added the "right" way to produce final color)
t_vec	ft_diffuse(t_hit *hit, t_light *light);
t_vec	ft_specular(t_hit *hit, t_vec incident, t_light *light, int alpha);
t_vec	ft_flare(t_hit *hit, t_line *ray, t_light *light);

// "utils"
// find reflected vec
t_vec	ft_reflect(t_vec incident, t_vec normal);
// make hit object corresponding to closest shape (in 'shapes') hit in the line
// of sight
int		ft_closest_hit(t_hit *hit, t_line *ray, t_shape_list *shapes);
// fill *writable* hit object
void	ft_make_hit(t_hit *hit, t_shape *shape, t_vec p);
// determine if the point hit is illuminated by 'light' (ie is not shadowed)
int		ft_shadowed(t_hit *hit, t_line *ray, t_scene *scene, t_light *light);

#endif

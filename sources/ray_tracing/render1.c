#include <math.h>
#include <stddef.h>
#include "shape.h"
#include "vec.h"
#include "utypes.h"
#include "render.h"

t_vec	ft_diffuse(t_hit *hit, t_light *light)
{
	float	lum;
	t_vec	to_light;
	t_vec	color;

	to_light = ft_diff(light->pos, hit->p);
	lum = light->intensity;
	ft_make_unit(&to_light);
	lum *= fabs(ft_dot(to_light, hit->n));
	color = ft_color(hit->p, hit->sh);
	return (ft_scaled(lum, ft_vec_mult(color, light->color)));
}

t_vec	ft_specular(t_hit *hit, t_vec incident, t_light *light, int alpha)
{
	t_vec	to_light;
	t_vec	reflected;
	float	cos;

	to_light = ft_diff(light->pos, hit->p);
	ft_make_unit(&to_light);
	reflected = ft_reflect(incident, hit->n);
	cos = ft_dot(reflected, to_light);
	if (cos > 0)
		return (ft_scaled(ft_fastexp(cos, alpha), light->color));
	else
		return (ft_vec(0, 0, 0));
}

static t_vec	ft_flares(t_hit *hit, t_line *ray, t_light_list *lights)
{
	t_vec	color;

	color = ft_vec(0, 0, 0);
	while (lights)
	{
		ft_add_to(&color, ft_flare(hit, ray, &lights->light));
		lights = lights->next;
	}
	return (color);
}

static t_vec	ft_light_loop(t_hit *hit, t_line *ray, t_scene *sce)
{
	t_vec			color;
	t_vec			add_me;
	t_light_list	*it;

	color = ft_vec(0, 0, 0);
	it = sce->lights;
	while (it)
	{
		if (!ft_shadowed(hit, ray, sce, &it->light))
		{
			add_me = ft_scaled(hit->sh->dif_coef, ft_diffuse(hit, &it->light));
			ft_add_to(&color, add_me);
			add_me = ft_specular(hit, ray->dir, &it->light, 32);
			ft_add_to(&color, ft_scaled(hit->sh->spec_coef, add_me));
		}
		ft_add_to(&color, ft_flare(hit, ray, &it->light));
		it = it->next;
	}
	return (color);
}

t_vec	ft_ray_color(t_line	*ray, t_scene *sce, int bounces, float thresh)
{
	t_vec	color;
	t_hit	hit;
	t_line	reflected;
	t_vec	refl_color;
	float	coef;

	if (!ft_closest_hit(&hit, ray, sce->shapes))
		return (ft_flares(NULL, ray, sce->lights));
	color = ft_vec_mult(sce->ambient_color, ft_color(hit.p, hit.sh));
	ft_scale(sce->ambient * hit.sh->dif_coef, &color);
	ft_add_to(&color, ft_light_loop(&hit, ray, sce));
	if (bounces > 0 && thresh > 1)
	{
		coef = hit.sh->refl_coef;
		reflected.dir = ft_reflect(ray->dir, hit.n);
		reflected.p = ft_vec_add(hit.p, ft_scaled(0.01, reflected.dir));
		if (hit.sh->bump_map
			&& ft_same_side(ft_normal(hit.p, hit.sh), reflected.dir, ray->dir))
			return (color);
		refl_color = ft_ray_color(&reflected, sce, bounces - 1, coef * thresh);
		ft_add_to(&color, ft_scaled(coef, refl_color));
	}
	return (color);
}

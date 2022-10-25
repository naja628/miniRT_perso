#include <math.h>
#include "shape.h"
#include "vec.h"
#include "line.h"
#include "bases.h"
#include "bump_mapping.h"
#include <stddef.h>

int	ft_intersect(float *t, t_line *ray, t_shape *s)
{
	const t_intersect_fun	funs[SHP_NTYPES]
		= {ft_sp_inter, ft_pl_inter, ft_cy_inter, ft_cn_inter};

	return (funs[s->type](t, ray, s->data));
}

static t_vec	ft_get_perturb(t_vec2 xy, float map_height, t_normals *bumps)
{
	int	x;
	int	y;

	xy.x = ft_fmod(xy.x, map_height);
	xy.y = ft_fmod(xy.y, map_height);
	x = (int) floor(xy.x / map_height * bumps->w);
	y = (int) floor(xy.y / map_height * bumps->h);
	return (bumps->data[x + y * bumps->w]);
}

t_vec	ft_normal(t_vec p, t_shape *s)
{
	const t_normal_fun	funs[SHP_NTYPES]
		= {ft_sp_normal, ft_pl_normal, ft_cy_normal, ft_cn_normal};
	t_vec				normal;
	t_basis				basis;
	t_vec2				xy;

	if (!s->bump_map)
		return (funs[s->type](p, s->data));
	xy = ft_map2d(p, s, &basis);
	normal = ft_get_perturb(xy, s->map_height, s->bump_map);
	if (s->type == SHP_SPHERE && (xy.x == 0)) // xy.x == 0 -> would div 0
	{
		normal.x /= sin(xy.y / ((t_sphere *)(s->data))->radius);
		ft_make_unit(&normal);
	}
	if (s->type == SHP_CYLIN && !(ft_near_zero(xy.y, 0.001)))
	{
		normal.x /= sqrt((t_cone *)(s->data)->slope);
	}
	normal = ft_in_basis(&basis, normal);
	return (normal);
}

t_vec2	ft_map2d(t_vec p, t_shape *s, t_basis *basis)
{
	const t_map2d	maps[SHP_NTYPES]
		= {ft_sp_map, ft_pl_map, ft_cy_map, ft_cn_map};

	return (maps[s->type](p, s->data, basis));
}

t_vec	ft_color(t_vec p, t_shape *s)
{
	const float	tile_sz = M_PI / 6;
	t_vec2		xy;
	float		test;

	if (!s->is_checkered)
		return (s->color);
	xy = ft_map2d(p, s, NULL);
	test = (ft_fmod(xy.x, 2 * tile_sz) - tile_sz);
	test *= (ft_fmod(xy.y, 2 * tile_sz) - tile_sz);
	// TODO maybe use super-dark grey / super light-white instead of 
	// black / white
	// or even super-dark grey / color
	if (test > 0)
		return (ft_vec(1, 1, 1));
	else
		return (ft_vec(0, 0, 0));
}

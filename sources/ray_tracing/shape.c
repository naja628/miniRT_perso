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

t_vec	ft_normal(t_vec p, t_shape *s)
{
	const t_normal_fun	funs[SHP_NTYPES]
		= {ft_sp_normal, ft_pl_normal, ft_cy_normal, ft_cn_normal};

	return (funs[s->type](p, s->data));
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
	if (test > 0)
		return (s->color);
	else
		return (ft_scaled(0.3, s->color));
}

#include <math.h>
#include "math_utils.h"
#include "vec.h"
#include "line.h"
#include "shape.h"
#include "bases.h"

int	ft_sp_inter(float *t, t_line *ray, void *sp_data)
{
	t_sphere	*sp;
	t_vec		v;
	float		c;
	float		ts[2];

	sp = sp_data;
	v = ft_diff(ray->p, sp->center);
	c = ft_sqnorm(v) - sp->radius * sp->radius;
	if (!ft_roots(ts, 2 * ft_dot(ray->dir, v), c) || ts[1] <= 0)
		return (0);
	else if (ts[0] > 0)
		*t = ts[0];
	else
		*t = ts[1];
	return (1);
}

t_vec	ft_sp_normal(t_vec p, void *sp_data)
{
	t_sphere	*sp;
	t_vec		n;

	sp = sp_data;
	n = ft_diff(p, sp->center);
	ft_scale(1.0 / sp->radius, &n);
	return (n);
}

static int	ft_handle_poles(t_vec2 xy, t_basis *basis, t_vec unit)
{
	if (ft_near_zero(xy.y, 0.001) || ft_near_zero(xy.y - M_PI, 0.001))
	{
		xy.x = 0;
		if (basis)
			ft_complete_basis2(unit, ft_vec(0, -1, 0), basis);
		return (1);
	}
	return (0);
}

// map to polar coordinated scaled to fit in [0, 1] x [0, 2]
t_vec2	ft_sp_map(t_vec p, void *sp_data, t_basis *basis)
{
	t_vec2		xy;
	t_vec		unit;
	t_sphere	*sp;

	sp = (t_sphere *) sp_data;
	unit = ft_diff(p, sp->center);
	ft_scale(1.0 / sp->radius, &unit);
	xy.y = ft_angle(ft_vec(0, 0, -1), unit);
	if (!ft_handle_poles(xy, basis, unit))
	{
		if (basis)
			ft_complete_basis2(unit, ft_vec(0, 0, -1), basis);
		unit.z = 0;
		ft_make_unit(&unit);
		xy.x = ft_angle(ft_vec(0, -1, 0), unit);
	}
	if (unit.x < 0)
		xy.x = 2 * M_PI - xy.x;
	xy.x *= sp->radius;
	xy.y *= sp->radius;
	return (xy);
}

#include <math.h>
#include <stddef.h>
#include "math_utils.h"
#include "vec.h"
#include "line.h"
#include "shape.h"
#include "bases.h"

static float	ft_hyp(float slope)
{
	return (sqrt(1 + slope * slope));
}

int ft_cn_inter(float *t, t_line *ray, void *cn_data)
{
	t_cone	*cn;
	t_cncomp	cp;
	int			i;
	float		ts[2];
	float		sqsl;

	cn = (t_cone *) cn_data;
	ft_para_perp(cn->dir, ft_diff(ray->p, cn->p), &(cp.ppara), &(cp.pperp));
	ft_para_perp(cn->dir, ray->dir, &(cp.dpara), &(cp.dperp));
	sqsl = cn->slope * cn->slope;
	cp.a = ft_sqnorm(cp.dperp) - sqsl * ft_sqnorm(cp.dpara);
// 	cp.b = ft_dot(cp.pperp, cp.dperp);
// 	cp.b -= cn->slope * ft_dot(cn->dir, cp.ppara) * ft_dot(cn->dir, cp.dpara);
// 	cp.b *= 2;
	cp.b = ft_dot(cp.dperp, cp.pperp) - sqsl * ft_dot(cp.ppara, cp.dpara);
	cp.b *= 2;
	cp.c = ft_sqnorm(cp.pperp) - sqsl * ft_sqnorm(cp.ppara);
	if (ft_near_zero(cp.a, 0.001) || !ft_roots(ts, cp.b / cp.a, cp.c / cp.a))
		return (0);
	i = 0;
	while (i < 2)
	{
		*t = ts[i];
		cp.height = ft_dot(cn->dir, ft_diff(ft_point_at_t(ray, *t), cn->p));
		if (*t >= 0 && 0 <= cp.height && cp.height <= cn->h)
			return (1);
		++i;
	}
	return (0);
}

t_vec	ft_cn_normal(t_vec p, void *cn_data)
{
	t_cone *cn;
	t_vec		normal;
	t_vec		para;
	float	height;
	float	hyp;
	
	cn = (t_cone *) cn_data;
	ft_para_perp(cn->dir, ft_diff(p, cn->p), &para, &normal);
	height = ft_dot(cn->dir, para);
	hyp = ft_hyp(cn->slope); 
	ft_scale(1.0 / (height * cn->slope * hyp), &normal);
	ft_add_to(&normal, ft_scaled(-(cn->slope / hyp), cn->dir));
	return (normal);
}

static void	ft_cn_basis(t_vec p, void *cn_data, t_basis *basis) 
{
	t_cone	*cn;
	t_vec	normal;
	t_vec	y_dir;

	cn = (t_cone *) cn_data;
	normal = ft_cn_normal(p, cn_data);
	y_dir = p - cn->p;
	ft_make_unit(&y_dir);
	ft_complete_basis2(normal, y_dir, basis);
}

// y goes to height, x goes to angle times radius
t_vec2	ft_cn_map(t_vec p, void *cn_data, t_basis *basis)
{
	t_cone		*cn;
	t_vec2		xy;
	t_vec		para;
	t_vec		perp;
	t_vec		angle_zero;

	cn = (t_cone *) cn_data;
	ft_para_perp(cn->dir, ft_diff(p, cn->p), &para, &perp);
	xy.y = ft_hyp(cn->slope) * ft_dot(para, cn->dir);
	ft_make_unit(&perp);
	if (basis)
		ft_cn_basis(p, cn_data, basis);
	// TODO decide if store angle-zero
	if (!ft_colin(cn->dir, ft_vec(1, 0, 0)))
		angle_zero = ft_cross(ft_vec(1, 0, 0), cn->dir);
	else
		angle_zero = ft_cross(cn->dir, ft_vec(0, 0, 1));
	ft_make_unit(&angle_zero);
	xy.x = ft_angle(angle_zero, perp);
	if (ft_dot(ft_cross(angle_zero, perp), cn->dir) < 0)
		xy.x = 2 * M_PI - xy.x;
// 	xy.x *= cn->slope; // TODO think
	return (xy);
}
// 
// 	t_cone *cn;
// 	t_vec2 xy;
// 	t_vec para;
// 	t_vec perp;
// 	t_vec angle_zero;
// 
// 	cn = (t_cone *) cn_data;
// 	// find height = y of point
// 	ft_para_perp(cn->dir, ft_diff(p, cn->p), &para, &perp);
// 	xy.y = ft_dot(para, cn->dir);
// 	// nomalize the perp component for angle computations
// 	ft_scale(1.0 / cn->slope * xy.y, &perp);
// 	// complete basis
// 	if (basis)
// 		ft_complete_basis2(ft_cn_normal(p, cn
// 		// arbitrary line cut (norminette temporary)
// 		_data), ft_scaled(-1, cn->dir), basis);
// 	// find angle between a "semi-arbitrary" angle-zero vector and the perp
// 	// use arc (= angle * radius) as x component
// 	// to fasten things up angle_zero could be a field of cn struct
// 	// (same vec is computed every time)
// 	if (!ft_colin(cn->dir, ft_vec(1, 0, 0)))
// 		angle_zero = ft_cross(ft_vec(1, 0, 0), cn->dir);
// 	else
// 		angle_zero = ft_cross(cn->dir, ft_vec(0, 0, 1));
// 	ft_make_unit(&angle_zero);
// 	xy.x = ft_angle(angle_zero, perp);
// 	if (ft_dot(ft_cross(angle_zero, perp), cn->dir) < 0) // simpler solution??
// 		xy.x = 2 * M_PI - xy.x;
// 	xy.x *= cn->slope * xy.y;
// 	return (xy);

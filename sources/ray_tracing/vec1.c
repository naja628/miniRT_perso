#include <math.h>
#include "vec.h"

// vec1.c init + adding operations

t_vec	ft_vec(float x, float y, float z)
{
	t_vec	u;

	u.x = x;
	u.y = y;
	u.z = z;
	return (u);
}

void	ft_add_to(t_vec *u, t_vec v)
{
	u->x += v.x;
	u->y += v.y;
	u->z += v.z;
}

t_vec	ft_vec_add(t_vec u, t_vec v)
{
	t_vec	w;

	w = u;
	ft_add_to(&w, v);
	return (w);
}

t_vec	ft_diff(t_vec p, t_vec q)
{
	return (ft_vec_add(p, ft_scaled(-1, q)));
}

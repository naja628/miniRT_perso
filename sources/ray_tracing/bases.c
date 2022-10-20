#include <math.h>
#include "bases.h"

// fill a *writable* t_basis struct 'basis' with vector e0, e1, e2
void	ft_set_basis(t_basis *basis, t_vec e0, t_vec e1, t_vec e2)
{
	basis->e0 = e0;
	basis->e1 = e1;
	basis->e2 = e2;
}

// given a *unit* vector u 
// complete u into an orthonormal basis, u, *v, *w 
// such that *v is in the direction of the cross product of 
// u and 'orient'
void	ft_complete_basis(t_vec u, t_vec orient, t_vec *v, t_vec *w)
{
	*v = ft_cross(u, orient);
	ft_make_unit(v);
	*w = ft_cross(u, *v);
}

// same as 'complete_basis' but uses a 't_basis' struct
// u will be e2
void	ft_complete_basis2(t_vec u, t_vec orient, t_basis *completed)
{
	completed->e2 = u;
	ft_complete_basis(u, orient, &completed->e0, &completed->e1);
}

// if u is a vector expressed in basis 'basis'
// compute its coordinates in the "canonical" xyz basis
t_vec	ft_in_basis(t_basis *basis, t_vec u)
{
	t_vec	ret;

	ret = ft_scaled(u.x, basis->e0);
	ft_add_to(&ret, ft_scaled(u.y, basis->e1));
	ft_add_to(&ret, ft_scaled(u.z, basis->e2));
	return (ret);
}

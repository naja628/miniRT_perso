#ifndef BASES_H
# define BASES_H

# include "vec.h"

typedef struct s_basis
{
	t_vec	e0;
	t_vec	e1;
	t_vec	e2;
}	t_basis;

// fill a *writable* t_basis struct 'basis' with vector e0, e1, e2
void	ft_set_basis(t_basis *basis, t_vec e0, t_vec e1, t_vec e2);

// given a *unit* vector u 
// complete u into an orthonormal basis, u, *v, *w 
// such that *v is in the direction of the cross product of 
// u and 'orient'
void	ft_complete_basis(t_vec u, t_vec orient, t_vec *v, t_vec *w);

// same as 'complete_basis' but uses a 't_basis' struct
// u will be e2
void	ft_complete_basis2(t_vec u, t_vec orient, t_basis *completed);

// if u is a vector expressed in basis 'basis'
// compute its coordinates in the "canonical" xyz basis
t_vec	ft_in_basis(t_basis *basis, t_vec u);

#endif

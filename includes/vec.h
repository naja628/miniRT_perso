#ifndef VEC_H
# define VEC_H

// 3d vector
typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

// returns a 3d vector with components x, y, z
t_vec	ft_vec(float x, float y, float z);

/*** ADDITION ***/

// return u + v
t_vec	ft_vec_add(t_vec u, t_vec v);

// v is added to *u in place
void	ft_add_to(t_vec *u, t_vec v);

// returns p - q
// note : needed because 'ft_vec_add(p, ft_scaled(-1, q))'
// is a bit verbose
t_vec	ft_diff(t_vec p, t_vec q);

/*** NORMS AND SCALING ***/

// returns the norm (length) of u
float	ft_norm(t_vec u);

// returns the square of the norm of u
// note : less computionally expensive than 'ft_norm'
// and often sufficient (for one's need)
float	ft_sqnorm(t_vec u);

// change u so that it is length 1
// (u still points in the same direction)
// * u shall be non-zero *
void	ft_make_unit(t_vec *u);

// returns u scaled by a factor of lambda.
// that is each of its components is multiplied by lambda
t_vec	ft_scaled(float lambda, t_vec u);
// scale *u by lambda in place
void	ft_scale(float lambda, t_vec *u);

/*** PRODUCTS ***/

// returns u x v, the cross product of u and v
t_vec	ft_cross(t_vec u, t_vec v);

// returns u . v, the dot/scalar product of u and v
float	ft_dot(t_vec u, t_vec v);

// component-wise multiplication
t_vec	ft_vec_mult(t_vec u, t_vec v);

#endif

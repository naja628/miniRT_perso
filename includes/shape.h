/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:36:06 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:36:06 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "line.h"
# include "utypes.h"
# include "bump_mapping.h"
# include "math_utils.h"
# include "bases.h"
# include "vec2.h"

# define SHP_NTYPES 4

typedef enum e_shapetype
{
	SHP_SPHERE = 0,
	SHP_PLANE = 1,
	SHP_CYLIN = 2,
	SHP_CONE = 3,
}	t_shapetype;

/************ GENERIC (interface) ************/

// represents a shape that can be one of several types
// (enumarated by t_shapetype).
// data is a void* meant to be cast to the right type
// that contain the shape's geometric data.
// Other fields give information about the look/color
// and feel of the material / surface.
typedef struct s_shape
{
	t_shapetype	type;
	void		*data;
	t_vec		color;
	int			is_checkered;
	float		dif_coef;
	float		spec_coef;
	float		refl_coef;
	t_normals	*bump_map;
	float		map_height;
}	t_shape;

// in the below functions, polymorphic-like behavior is acheived 
// via hardcoding an array of functions that are the shape-specific
// implementation and calling the right one based on the shape's 'type'. 
// they must thus be of the relevant type (cf typedefs below)
typedef int				(*t_intersect_fun)(float *, t_line *, void *);
typedef t_vec			(*t_normal_fun)(t_vec, void *);
typedef t_vec2			(*t_map2d)(t_vec, void *, t_basis *);

// functions on shapes that are often dispatchers to the specific
// implementations for each shape.

// if 'ray' point to a line p + t.d (p a point, d a directional vector)
// t shall be a pointer to a *writable* float.
// return 1 if the line intersects '*s' for at least one positive value 
// of t, in this case, t will point to smallest positive t for which 
// there is an intersection.
// otherwise return 0 and ignore '*t'
int		ft_intersect(float *t, t_line *ray, t_shape *s);

// given p a point approximately on the shape '*s'
// return the normal to the surface of s at the point p
// (points outwards)
t_vec	ft_normal(t_vec p, t_shape *s);

// implementation specific type used by `ft_bumped_normal`
// in .h bc of norminette, should be considered opaque
//
// forward declare below types:
typedef struct s_sphere	t_sphere;
typedef struct s_cone	t_cone;
typedef union u_sp_cn
{
	t_sphere	*sp;
	t_cone		*cn;
}	t_sp_cn;

// When using bump mapping, returns the normal accounting 
// for it. (return the normal otherwise)
// !! this function breaks encapsulation,
// it contains code needed to rescale the normals
// depending on the way the surface is 2d mapped.
t_vec	ft_bumped_normal(t_vec p, t_shape *s);

// defines a map from the surface of s to 2d space
// Associates to p the image via this map (returned as t_vec2)
// optionally, if 'basis' is non-null
// it *shall* then point to a writable to basis struct, which 
// will be filled with {e0, e1, e2} vectors such that:
// * the basis is orthonormal
// * they are all unit vectors,
// * e2 is the normal
// * e0 (e1) points in the direction of "increasing" xs (ys)
t_vec2	ft_map2d(t_vec p, t_shape *s, t_basis *basis);

// returns the color of the point p on the surface s
// (not always s->color, as the surface might be checkered
// + easily extensible to allow for texturing etc)
t_vec	ft_color(t_vec p, t_shape *s);

/********* SHAPE SPECIFIC IMPLEMENTATIONS *******/

// pl
typedef struct s_plane
{
	t_vec	p;
	t_vec	dir;
}	t_plane;

int		ft_pl_inter(float *t, t_line *ray, void *pl_data);
t_vec	ft_pl_normal(t_vec p, void *pl_data);
t_vec2	ft_pl_map(t_vec p, void *pl_data, t_basis *basis);

// sp
typedef struct s_sphere
{
	t_vec	center;
	float	radius;
}	t_sphere;

int		ft_sp_inter(float *t, t_line *ray, void *sp_data);
t_vec	ft_sp_normal(t_vec p, void *sp_data);
t_vec2	ft_sp_map(t_vec p, void *sp_data, t_basis *basis);

// cy
typedef struct s_cylinder
{
	t_vec	p;
	t_vec	dir;
	float	r;
	float	h;
}	t_cylinder;

// implementation specific struct 
// store intermediate computations when finding intersections
typedef struct s_cycomp
{
	t_vec	pperp;
	t_vec	ppara;
	t_vec	dperp;
	t_vec	dpara;
	float	height;
	float	a;
	float	b;
	float	c;
}	t_cycomp;

int		ft_cy_inter(float *t, t_line *ray, void *cy_data);
t_vec	ft_cy_normal(t_vec p, void *cy_data);
t_vec2	ft_cy_map(t_vec p, void *cy_data, t_basis *basis);

//cn
typedef struct s_cone
{
	t_vec	p;
	t_vec	dir;
	float	slope;
	float	h;
}	t_cone;

// implementation specific struct
typedef struct s_cncomp
{
	t_vec	pperp;
	t_vec	ppara;
	t_vec	dperp;
	t_vec	dpara;
	float	height;
	float	a;
	float	b;
	float	c;
}	t_cncomp;

int		ft_cn_inter(float *t, t_line *ray, void *cn_data);
t_vec	ft_cn_normal(t_vec p, void *cn_data);
t_vec2	ft_cn_map(t_vec p, void *cn_data, t_basis *basis);

#endif

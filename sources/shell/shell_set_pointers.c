#include "shell.h"

void	null_pointers(t_shell_data *t)
{
	t->rot_dir = NULL;
	t->mv_p = NULL;
	t->w = NULL;
	t->h = NULL;
}

typedef union u_poly
{
	void		*unknown;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_cone		*cn;
}			t_poly;

static void	set_pointers_shape(t_shell_data *t, t_shape *s, t_poly *poly)
{
	if (s->type == SHP_SPHERE)
	{
		t->mv_p = &(poly->sp->center);
		t->w = &(poly->sp->radius);
	}
	else if (s->type == SHP_PLANE)
	{
		t->mv_p = &(poly->pl->p);
		t->rot_dir = &(poly->pl->dir);
	}
	else if (s->type == SHP_CONE)
	{
		t->mv_p = &(poly->cn->p);
		t->rot_dir = &(poly->cn->dir);
		t->w = &(poly->cn->slope);
		t->h = &(poly->cn->h);
	}
	else if (s->type == SHP_CYLIN)
	{
		t->mv_p = &(poly->cy->p);
		t->rot_dir = &(poly->cy->dir);
		t->w = &(poly->cy->r);
		t->h = &(poly->cy->h);
	}
}

void	set_pointers(t_shell_data *t)
{
	t_poly	poly;
	t_shape	*s;

	null_pointers(t);
	if (t->select_type == LSC_SHAPE && t->its != NULL)
	{
		s = &(t->its->shape);
		poly.unknown = s->data;
		set_pointers_shape(t, s, &poly);
	}
	if (t->select_type == LSC_LIGHT && t->itl != NULL)
		t->mv_p = &(t->itl->light.pos);
	if (t->select_type == LSC_CAMERA)
		t->mv_p = &(t->data->cam.viewpoint);
}

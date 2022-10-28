#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "shell.h"
#include "render_scr.h"

// we need the commands :
// l, s, c, n, w, h, mv, rot, render
// optional :
// new, del, hl, print (p?), save (export rt)
// note if new -> use mk_camscreen in parsing instead of main

void	null_pointers(t_shell_data *t)
{
	t->rot_dir = NULL;
	t->mv_p = NULL;
	t->w = NULL;
	t->h = NULL;
}

typedef union u_poly
{
	void	*unknown;
	t_sphere *sp;
	t_plane	*pl;
	t_cylinder  *cy;
	t_cone	*cn;
}	t_poly;

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

void	init_shell_data(t_shell_data *t, t_parse *data, t_scr *scr)
{
	t->data = data;
	t->select_type = LSC_SHAPE;
	null_pointers(t);
	t->its = data->scene.shapes;
	t->itl = data->scene.lights;
	set_pointers(t);
	t->args_line = NULL;
	t->scr = scr;
// 	t->hl = 0;
}

int	cmd_l(t_shell_data *t)
{
	t->select_type = LSC_LIGHT;
	return (0);
}

int	cmd_s(t_shell_data *t)
{
	t->select_type = LSC_SHAPE;
	return (0);
}

int	cmd_c(t_shell_data *t)
{
	t->select_type = LSC_CAMERA;
	return (0);
}

int	cmd_n(t_shell_data *t)
{
	if (t->select_type == LSC_LIGHT && t->itl != NULL)
	{
		t->itl = t->itl->next;
		if (!(t->itl))
			t->itl = t->data->scene.lights;
	}
	if (t->select_type == LSC_SHAPE && t->its != NULL)
	{
		t->its = t->its->next;
		if (!(t->its))
			t->its = t->data->scene.shapes;
	}
	if (t->select_type == LSC_CAMERA)
		return (printf("only one camera\n"));
	return (0);
}

int	cmd_w(t_shell_data *t)
{
	float read_w;
	int error;

	error = 0;
	if (!(t->w))
		return (printf("no such attribute\n"));
	read_w = ft_atof_minirt(&(t->args_line), &error);
	want_positive(read_w, &error);
	if (!error)
		*(t->w) = read_w / 2;
	else
		return (printf("expected positive float after w\n"));
	return (0);
}

int	cmd_h(t_shell_data *t)
{
	float read_h;
	int error;

	error = 0;
	if (!(t->h))
		return (printf("no such attribute\n"));
	read_h = ft_atof_minirt(&(t->args_line), &error);
	want_positive(read_h, &error);
	if (!error)
		*(t->h) = read_h;
	else
		return (printf("expected positive float after h\n"));
	return (0);
}

int	cmd_mv(t_shell_data *t)
{
	t_vec	motion;
	int 	error;

	error = 0;
	if (!(t->mv_p)) // never happens?
		return (printf("element cannot be moved\n"));
	motion = read_vec(&(t->args_line), &error);
	if (!error)
		ft_add_to(t->mv_p, motion);
	else
		return (printf("expected vector\n"));
	return (0);
}

int	cmd_render(t_shell_data *t)
{
	printf("rendering...\n");
	ft_render_scr(t->scr, &(t->data->cam), &(t->data->scene));
	mlx_put_image_to_window(t->scr->mlx, t->scr->win, t->scr->imptr, 0, 0);
	printf("done\n");
	return (0);
}

/*** cmd_rot ***/
static t_vec	rot_x(t_vec u, float theta)
{
	t_vec	v;

	v.x = u.x;
	v.y = ft_dot(u, ft_vec(0, cos(theta), -sin(theta)));
	v.z = ft_dot(u, ft_vec(0, sin(theta), cos(theta)));
	return (v);
}

static void	rot_basis(t_vec *u, int iaxis)
{
	float	tmp;

	iaxis %= 3;
	if (iaxis < 0)
		iaxis += 3;
	while (iaxis)
	{
		tmp = u->x;
		u->x = u->y;
		u->y = u->z;
		u->z = tmp;
		--iaxis;
	}
}

static void	rot(t_vec *u, int iaxis, float theta)
{

	theta = -theta; // why are rotations the wrong way around??
	rot_basis(u, iaxis);
	*u = rot_x(*u, theta);
	rot_basis(u, -iaxis);
}

static void	cam_rot(t_camera *cam, int iaxis, float theta)
{
	rot(&(cam->corner), iaxis, theta);
	rot(&(cam->dir), iaxis, theta);
	rot(&(cam->hz_dir), iaxis, theta);
	rot(&(cam->vt_dir), iaxis, theta);
}

int	cmd_rot(t_shell_data *t)
{
	int 	iaxis;
	int		error;
	char	*line;
	float	theta;
	
	error = 0;
	line = t->args_line;
	if (t->select_type != LSC_CAMERA && !t->rot_dir)
		return (printf("rotations not allowed for this element\n"));
	if (!(line[0] == 'x' || line[0] == 'y' || line[0] == 'z')
		|| !(line[1] == ' ' || line[1] == '\t'))
		return (printf("expected axis as arg 1 (x, y or z)\n"));
	iaxis = line[0] - 'x';
	line = skip_spaces(line + 1);
	theta = ft_atof_minirt(&line, &error);
	if (error == EXPECTED_NUMBER)
		return (printf("expected angle in radian as arg 2\n"));
	if (t->select_type == LSC_CAMERA)
		cam_rot(&(t->data->cam), iaxis, theta);
	else
		rot(t->rot_dir, iaxis, theta);
	return (0);
}
/*** end cmd rot ***/

/*** dispatcher ***/
static void init_dispatch(t_dispatch *t, char *cmd, t_cmd fun)
{
	t->cmd = cmd;
	t->fun = fun;
}

#define NCMD 9
t_dispatch *dispatch_table(void)
{
	static t_dispatch	t[NCMD];
	static int			init = 0;

	if (!init)
	{
		init_dispatch(t + 0, "l", cmd_l);
		init_dispatch(t + 1, "s", cmd_s);
		init_dispatch(t + 2, "c", cmd_c);
		init_dispatch(t + 3, "n", cmd_n);
		init_dispatch(t + 4, "w", cmd_w);
		init_dispatch(t + 5, "h", cmd_h);
		init_dispatch(t + 6, "mv", cmd_mv);
		init_dispatch(t + 7, "rot", cmd_rot);
		init_dispatch(t + 8, "render", cmd_render);
		init = 1;
	}
	return (t);
}

int dispatch(char *line, t_shell_data *t)
{
	int i;
	int cmd_len;
	t_dispatch *table;

	i = 0;
	table = dispatch_table();
	while (i < NCMD)
	{
		cmd_len = ft_strlen(table[i].cmd);
		if (id_match(line, table[i].cmd, cmd_len))
		{	
			t->args_line = line + cmd_len;
			t->args_line = skip_spaces(t->args_line);
			return (table[i].fun(t));
		}
		++i;
	}
	return (printf("unknown command\n"));
}

#undef NCMD
/*** end dispatcher ***/

void	exe_line(char *line, t_shell_data *t)
{
	line = skip_spaces(line);
	if (*line == '\n' || *line == '\0')
		return ;
	printf("executing line : %s", line);
	if (dispatch(line, t))
		printf("error.\n");
	else
		printf("done.\n");
	set_pointers(t);
}

// HOOK
#define LCLICK 1
int minirt_shell_hook(int button, int x, int y, t_shell_data *t)
{
	char	*line;

	(void) x;
	(void) y;
	if (button != LCLICK)
		return (0);
	line = get_next_line(0);
	if (!line)
		return (0);
	exe_line(line, t);
	free (line);
	return (0);
}
//  for highlights
// 	mlx_put_image_to_window(t->scr->mlx, t->scr->win, t->scr->imptr, 0, 0);
// 	if (t->hl)
// 		draw_highlight(t);
#undef LCLICK

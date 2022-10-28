// to be super safe with rotation / translation things implement a shell with 
// the following commands
// l -> lights
// s -> shapes
// c -> camera
// n -> select next elem
// w -> width (diam for sp etc)
// h -> height (cone and cy)
// mv vec -> translation
// render -> render
// new -> read rest of the line like rt file
// del -> del
// TODO
// hl -> toggle highlight
// rot axis angle -> rotation
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "shell.h"
#include "render_scr.h"

// typedef enum e_lsc {LSC_LIGHT, LSC_CAMERA, LSC_SHAPE} t_lsc;
// typedef struct s_shell_data
// {
// 	t_parse	*data;
// 	t_lsc	select_type;
// 	t_vec	*rot_dir;
// 	t_vec	*mv_p;
// 	int		*h;
// 	int		*w;
// 	t_shape_list *its;
// 	t_light_list *itl;
// 	char *args_line;
// 	t_scr *scr;
// 	int hl;
// 	// dispatch table? 
// }	t_shell_data;

void	re_null(t_shell_data *t)
{
	t->rot_dir = NULL;
	t->mv_p = NULL;
	t->w = NULL;
	t->h = NULL;
}

void	init_shell_data(t_shell_data *t, t_parse *data, t_scr *scr)
{
	t->data = data;
	t->select_type = LSC_SHAPE;
	re_null(t);
	t->its = data->scene.shapes;
	set_pointers(t, &(t->its->shape));
	t->itl = data->scene.lights;
	t->args_line = NULL;
	t->scr = scr;
	t->hl = 0;
}

void	cmd_l(t_shell_data *t)
{
	t->select_type = LSC_LIGHT;
	re_null(t);
	if (t->itl != NULL)
		t->mv_p = &(t->itl->light.pos);
}

void	cmd_s(t_shell_data *t)
{
	re_null(t);
	t->select_type = LSC_SHAPE;
	if (t->its != NULL)
		set_pointers(t, &(t->its->shape));
}

void	cmd_c(t_shell_data *t)
{
	re_null(t);
	t->select_type = LSC_CAMERA;
	t->mv_p = &(t->data->cam.viewpoint);
	t->rot_dir = &(t->data->cam.dir);
}


typedef union u_poly
{
	void	*unknown;
	t_sphere *sp;
	t_plane	*pl;
	t_cylinder  *cy;
	t_cone	*cn;
}	t_poly;

static void	set_pointers_helper(t_shell_data *t, t_shape *s, t_poly *poly)
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

void	set_pointers(t_shell_data *t, t_shape *s)
{
	t_poly	poly;

	poly.unknown = s->data;
	set_pointers_helper(t, s, &poly);
}

void	cmd_n(t_shell_data *t)
{
	re_null(t);
	if (t->select_type == LSC_LIGHT && t->itl != NULL)
	{
		t->itl = t->itl->next;
		if (!(t->itl))
			t->itl = t->data->scene.lights;
		t->mv_p = &(t->itl->light.pos);
	}
	else if (t->select_type == LSC_SHAPE && t->its != NULL)
	{
		t->its = t->its->next;
		if (!(t->its))
			t->its = t->data->scene.shapes;
		set_pointers(t, &(t->its->shape));
	}
	else if (t->select_type == LSC_CAMERA)
	{
		printf("only one camera\n");
	}
}

void	cmd_w(t_shell_data *t)
{
	float read_w;
	int error;

	error = 0;
	if (!(t->w))
	{
		printf("no such attribute\n");
		return ;
	}
	read_w = ft_atof_minirt(&(t->args_line), &error);
	want_positive(read_w, &error);
	if (!error)
		*(t->w) = read_w / 2;
	else
		printf("invalid arguments to cmd\n");
}

void	cmd_h(t_shell_data *t)
{
	float read_h;
	int error;

	error = 0;
	if (!(t->h))
	{
		printf("no such attribute\n");
		return ;
	}
	read_h = ft_atof_minirt(&(t->args_line), &error);
	want_positive(read_h, &error);
	if (!error)
		*(t->h) = read_h;
	else
		printf("invalid arguments to cmd\n");
}

void	cmd_mv(t_shell_data *t)
{
	t_vec	motion;
	int 	error;

	error = 0;
	if (!(t->mv_p)) // never happens?
	{
		printf("element cannot be moved\n");
		return ;
	}
	motion = read_vec(&(t->args_line), &error);
	if (!error)
	{
		ft_add_to(t->mv_p, motion);
	}
	else
		printf("invalid arguments to cmd\n");
}

// TODO
// hl -> toggle highlight
// rot axis angle -> rotation

void	cmd_render(t_shell_data *t)
{
// 	t_camera	*cam;
// 
// 	if (t->cam_change)
// 	{
// 		cam = t->data->cam;
// 		ft_mk_camscreen(cam, (float) 700 / 1000);
// 		t->cam_change = 0;
// 	}
	printf("rendering...\n");
	ft_render_scr(t->scr, &(t->data->cam), &(t->data->scene));
	mlx_put_image_to_window(t->scr->mlx, t->scr->win, t->scr->imptr, 0, 0);
	printf("done\n");
}

void	cmd_new(t_shell_data *t)
{
	int error;
	t_parse fake_data;

	init_intel(&fake_data);
	fake_data.mlx = t->data->mlx;
	fake_data.line = t->args_line;
	error = read_id(&fake_data);
	ft_free_shapes(fake_data.scene.shapes);
	ft_free_lights(fake_data.scene.lights);
	if (error)
		print_error(error, t->args_line);
	else
	{
		t->data->line = t->args_line;
		read_id(t->data);
// 		if (*args_line == 'C')
// 			cam_change = 1;
		t->its = t->data->scene.shapes;
		t->itl = t->data->scene.lights;
	}
}

// del file

static void	del_light(t_light_list *lights, t_light_list **itl)
{
	t_light_list *prevl;

	prevl = lights;
	while (prevl && prevl != *itl)
		prevl = prevl->next;
	if (prevl)
	{
		prevl->next = (*itl)->next;
		free(*itl);
		if (prevl == *itl)
			*itl = NULL;
		else
		{
			*itl = prevl->next;
			if (!(*itl))
				*itl = lights;
		}
	}
}

static void	del_shape(t_shape_list *shapes, t_shape_list **its)
{
	t_shape_list *prevs;
	
	prevs = shapes;
	while (prevs && prevs != *its)
		prevs = prevs->next;
	if (prevs)
	{
		prevs->next = (*its)->next;
		free((*its)->shape.data);
		if ((*its)->shape.bump_map)
		{
			free((*its)->shape.bump_map->data);
			free((*its)->shape.bump_map);
		}
		free(*its);
		if (prevs == *its)
			*its = NULL;
		else
		{
			*its = prevs->next;
			if (!(*its))
				*its = shapes;
		}
	}
}

void	cmd_del(t_shell_data *t)
{
	if (t->select_type == LSC_CAMERA)
		printf("cannot delete camera\n");
	if (t->select_type == LSC_LIGHT)
		del_light(t->data->scene.lights, &(t->itl));
	if (t->select_type == LSC_SHAPE)
		del_shape(t->data->scene.shapes, &(t->its));
}
// end del file

// rot file
#include "debug.h"
static t_vec	rot_x(t_vec u, float theta)
{
	t_vec	v;

	v.x = u.x;
	v.y = ft_dot(u, ft_vec(0, cos(theta), -sin(theta)));
	v.z = ft_dot(u, ft_vec(0, sin(theta), cos(theta)));
	return (v);
}

static void	rot_basis(t_vec *u, int rot)
{
	float	tmp;

	rot %= 3;
	if (rot < 0)
		rot += 3;
	while (rot)
	{
		tmp = u->x;
		u->x = u->y;
		u->y = u->z;
		u->z = tmp;
		--rot;
	}
}

static t_vec	rot(t_vec u, int iaxis, float theta)
{
	t_vec v;

	theta = -theta; // why are rotations the wrong way around??
	v = u;
	rot_basis(&v, iaxis);
	print_vec("new basis", v);
	v = rot_x(v, theta);
	print_vec("rot'd", v);
	rot_basis(&v, -iaxis);
	print_vec("old basis", v);
	return (v);
}

static void	cam_rot(t_camera *cam, int iaxis, float theta)
{
	print_vec("old corner", cam->corner);
	print_vec("old dir", cam->dir);
	print_vec("old hz", cam->hz_dir);
	print_vec("old vt", cam->vt_dir);
	cam->corner = rot(cam->corner, iaxis, theta);
	cam->dir = rot(cam->dir, iaxis, theta);
	cam->hz_dir = rot(cam->hz_dir, iaxis, theta);
	cam->vt_dir = rot(cam->vt_dir, iaxis, theta);
	print_vec("new corner", cam->corner);
	print_vec("new dir", cam->dir);
	print_vec("new hz", cam->hz_dir);
	print_vec("new vt", cam->vt_dir);
}

void	cmd_rot(t_shell_data *t)
{
	int 	iaxis;
	int		error;
	char	*line;
	float	angle;
	
	error = 0;
	line = t->args_line;
	if (!t->rot_dir)
	{
		printf("rotations not allowed for this element\n");
		return ;
	}
	if (!(line[0] == 'x' || line[0] == 'y' || line[0] == 'z')
			|| !(line[1] == ' ' || line[1] == '\t'))
	{
		printf("expected axis (x, y or z)\n");
		return ;
	}
	iaxis = line[0] - 'x';
	line = skip_spaces(line + 1);
	angle = ft_atof_minirt(&line, &error);
	if (error == EXPECTED_NUMBER)
	{
		printf("unspecified angle\n");
		return ;
	}
	if (t->select_type == LSC_CAMERA)
		cam_rot(&(t->data->cam), iaxis, angle);
	else
	{
		print_vec("dir", *(t->rot_dir));
		*(t->rot_dir) = rot(*(t->rot_dir), iaxis, angle);
		print_vec("dir", *(t->rot_dir));
	}
}

// int	norminette_trick(t_shell_data *t)
// {
// 	int 	iaxis;
// 	int		error;
// 	char	*line;
// 	float	angle;
// 	
// 	error = 0;
// 	line = t->args_line;
// 	if (!t->rot_dir)
// 		return (printf("rotations not allowed for this element\n"));
// 	if (!(line[0] == 'x' || line[0] == 'y' || line[0] == 'z')
// 			|| !(line[1] == ' ' || line[1] == '\t'))
// 		return (printf("expected axis (x, y or z)\n"));
// 	iaxis = line[0] - 'x';
// 	line = skip_spaces(line + 1);
// 	angle = ft_atof_minirt(&line, &error);
// 	if (error == EXPECTED_NUMBER)
// 		return (printf("unspecified angle\n"));
// 	if (t->select_type == LSC_CAMERA)
// 		cam_rot(&(t->data->cam), iaxis, angle);
// 	else
// 		*(t->rot_dir) = rot(*(t->rot_dir), iaxis, angle);
// 	return (0);
// }
// 
// void cmd_rot(t_shell_data *t)
// {
// 	norminette_trick(t);
// }

// end rot file

// highlight file
static t_vec	find_point_on_screen(t_camera *cam, t_vec p)
{
	t_plane	camscr_pl;
	t_line	to_p;
	float	t;

	camscr_pl.p = cam->corner;
	camscr_pl.dir = cam->dir;
	
	to_p.p = cam->viewpoint;
	to_p.dir = ft_diff(p, to_p.p);
	ft_make_unit(&(to_p.dir));

	if (!ft_pl_inter(&t, &to_p, &camscr_pl)) // needs void * cast?
		return (ft_vec(-1, -1, -1));

	return (ft_diff(ft_point_at_t(&to_p, t), cam->viewpoint));
}
	
static void	to_pix_coord(int *x, int *y, t_vec p, t_shell_data *t)
{
	float		xf;
	float		yf;
	t_camera	*cam;
	t_scr		*scr;

	cam = &(t->data->cam);
	scr = t->scr;
	xf = ft_dot(cam->hz_dir, p);
	yf = ft_dot(cam->vt_dir, p);
	*x = xf / scr->w;
	*y = yf / scr->w;
}

static void	draw_sqdot(int x, int y, t_scr *scr)
{
	const int half_size = 2;
	const int color = 0xff00ff;
	int dx;
	int dy;

	dx = -half_size;
	while (dx <= half_size)
	{
		dy = -half_size;
		while (dy <= half_size)
		{
			if (0 <= x + dx && x + dx < (int)(scr->w)
				&& 0 <= y + dy && y + dy < (int)(scr->h))
				// check useful? (TODO)
				mlx_pixel_put(scr->mlx, scr->win, x + dx, y + dy, color);
			++dy;
		}
		++dx;
	}
}

void	draw_highlight(t_shell_data *t)
{
	int		x;
	int		y;
	t_vec	scr_p;

	scr_p = find_point_on_screen(&(t->data->cam), *(t->mv_p));
	to_pix_coord(&x, &y, scr_p, t);
	draw_sqdot(x, y, t->scr);
}
	
void	cmd_hl(t_shell_data *t)
{
	t->hl = !(t->hl);
}
// end highlights file

// dispatcher

// typedef t_cmd void (*fun)(t_shell_data *);
// typedef struct s_dispatch
// {
// 	char	*cmd;
// 	t_cmd	fun;
// }	t_dispatch;
// 
static void init_dispatch(t_dispatch *t, char *cmd, t_cmd fun)
{
	t->cmd = cmd;
	t->fun = fun;
}

#define NCMD 12
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
		init_dispatch(t + 9, "new", cmd_new);
		init_dispatch(t + 10, "del", cmd_del);
		init_dispatch(t + 11, "hl", cmd_hl);
		init = 1;
	}
	return (t);
}

void dispatch(char *line, t_shell_data *t)
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
			table[i].fun(t);
			return ;
		}
		++i;
	}
	printf("unknown command\n");
}
#undef NCMD

// hook with mlx_loop_hook
int minirt_shell(t_shell_data *t)
{
	char	*line;

	line = get_next_line(0);
	if (!line)
		return (0);
	dispatch(line, t);
	mlx_put_image_to_window(t->scr->mlx, t->scr->win, t->scr->imptr, 0, 0);
	if (t->hl)
		draw_highlight(t);
	free (line);
	return (0);
}

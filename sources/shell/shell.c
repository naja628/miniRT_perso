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

typedef enum e_lsc {LSC_LIGHT, LSC_CAMERA, LSC_SHAPE} t_lsc;
typedef struct s_shell_data
{
	t_parse	*data;
	t_lsc	select_type;
	t_vec	*rot_dir;
	t_vec	*mv_p;
	int		*h;
	int		*w;
	t_shape_list *its;
	t_light_list *itl;
	int	cam_change;
	char *args_line;
	t_scr *scr;
	int hl;
	// dispatch table? 
}	t_shell_data;

void	re_null(t_shell_data *t)
{
	rot_dir = NULL;
	mv_p = NULL;
	w = NULL;
	h = NULL;
}

void	init_shell_data(t_shell_data *t, t_parse *data, t_scr *scr)
{
	t->data = data;
	t->select_type = LSC_SHAPE;
	t->re_null(t);
	t->its = data->scene.shapes;
	t->itl = data->scene.lights;
	t->args_line = NULL;
	t->cam_change = 0; // maybe set to 1 and call cmd_render in main
	t->scr = scr;
}

void	cmd_l(t_shell_data *t)
{
	t->select_type = LSC_LIGHT;
	if (t->itl != NULL)
		mv_p = &(itl->light.p);
}

void	cmd_s(t_shell_data *t)
{
	t->select_type = LSC_SHAPE;
	if (t->its != NULL)
		set_pointers(t, its->shape);
}

void	cmd_c(t_shell_data *t)
{
	t->select_type = LSC_CAMERA;
	mv_p = &(t->cam.p);
	rot_dir = &(t->cam.dir);
}

typedef union u_poly
{
	t_sphere *sp;
	t_plane	*pl;
	t_cylinder  *cy;
	t_cone	*cn;
}	t_poly;

void	set_pointers_helper(t_shell_data *t, t_shape *s, t_poly *poly)
{
	if (s->type == SHP_SPHERE)
	{
		t->mv_p = &(poly->sp->center);
		t->w = &(poly->sp->r);
	}
	else if (s->type == SHP_PLANE)
	{
		t->mv_p = &(poly->pl->p);
		t->rot_dir = &(poly->pl->dir);
	}
	else if (s->type == SHP_CONE)
	{
		t->mv_p = &(poly->cn->p);
		t->rot_dir = &(poly->cn->r);
		t->w = &(poly->cn->slope);
		t->h = &(poly->cn->h);
	}
	else if (s->type == SHP_CYLIN)
	{
		t->mv_p = &(poly->cy->p);
		t->rot_dir = &(poly->cy->r);
		t->w = &(poly->cy->r);
		t->h = &(poly->cy->h);
	}
}

void	set_pointers(t_shell_data *t, t_shape *s)
{
	t_poly	poly;

	poly = s->data;
	set_pointers_helper(t, s, &poly);
}

void	cmd_n(t_shell_data *t)
{
	re_null(t);
	if (t->select_type == LSC_LIGHT && itl != NULL)
	{
		t->itl = t->itl->next || t->data->scene.lights;
		mv_p = &(itl->light.p);
	}
	else if (t->select_type == LSC_SHAPE && its != NULL)
	{
		t->its = t->its->next || t->data->scene.shapes;
		set_pointers(t, its->shape);
	}
	else if (t->select_type == LSC_CAMERA)
	{
		printf("only one camera\n");
	}
}

void	cmd_w(t_shell_data *t)
{
	int read_w;
	int error;

	line = t->args_line;
	if (!(t->w))
	{
		printf("no such attribute\n");
		return ;
	}
	read_w = ft_atoi_minirt(&(t->args_line), &error);
	want_positive(read_w, &error);
	if (!error)
		*(t->w) = read_w / 2;
	else
		printf("invalid arguments to cmd\n");
}

void	cmd_h(t_shell_data *t)
{
	int read_h;
	int error;

	line = t->args_line;
	if (!(t->h))
	{
		printf("no such attribute\n");
		return ;
	}
	read_h = ft_atoi_minirt(&(t->args_line), &error);
	want_positive(read_h, &error);
	if (!error)
		*(t->h) = read_h;
	else
		printf("invalid arguments to cmd\n");
}

void	cmd_mv(t_shell_data *t)
{
	int	read_vec;
	int error;

	line = t->args_line;
	if (!(t->mv_p)) // never happens?
	{
		printf("element cannot be moved\n");
		return ;
	}
	read_vec = read_vec(&(t->args_line), &error);
	if (!error)
	{
		ft_add_to(t->mv_p, read_vec);
		if (t->select_type == LSC_CAMERA)
			t->cam_change = 1;
	}
	else
		printf("invalid arguments to cmd\n");
}

// TODO
// hl -> toggle highlight
// rot axis angle -> rotation

void	cmd_render(t_shell_data *t)
{
	t_camera	*cam;

	if (t->cam_change)
	{
		cam = t->data->cam;
		ft_mk_camscreen(cam, (float) 700 / 1000);
		t->cam_change = 0;
	}
	printf("rendering...");
	ft_render_scr(t->scr, t->data->cam, t->data->scene);
	mlx_put_image_to_window(t->scr.mlx, t->scr.win, t->scr.imptr, 0, 0);
	printf("done\n");
}

void	cmd_new(t_shell_data *t)
{
	int error;
	t_parse fake_data;

	init_intel(&fake_data);
	fake_data.mlx = t->data->mlx;
	fake_data.line = args_line;
	error = read_id(&fake_data);
	ft_free_shapes(fake_data.scene.shapes);
	ft_free_lights(fake_data.scene.lights);
	if (error)
		print_error(error, t->args_line);
	else
	{
		t->data.line = args_line;
		read_id(t->data);
		if (*args_line == 'C')
			cam_change = 1;
		t->its = t->data.scene.shapes;
		t->itl = t->data.scene.lights;
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
			*itl = prevl->next || lights;
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
			*its = prevs->next || shapes;
	}
}

void	cmd_del(t_shell_data *t)
{
	t_light_list *prevl;
	t_light_list *prevs;

	if (t->select_type == LSC_CAMERA)
		printf("cannot delete camera\n");
	if (t->select_type == LSC_LIGHT)
		del_light(t->data.scene.lights, &(t->itl));
	if (t->select_type == LSC_SHAPE)
		del_shape(t->data.scene.shapes, &(t->its));
}
// end del file

// rot
t_vec	rot_x(t_vec u, float theta)
{
	t_vec	v;

	v.x = u.x;
	v.y = ft_dot(u, ft_vec(0, cos(theta), -sin(theta)));
	v.z = ft_dot(u, ft_vec(0, sin(theta), cos(theta)));
	return (v);
}

void	rot_basis(t_vec *u, int rot)
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
	}
}

void	cmd_rot(t_shell_data *t)
{
	int 	basis_rot;
	int		errror;
	char	*line;
	float	angle;
	
	if (!t->rot_dir)
	{
		printf("rotations not allowed for this element\n");
		return ;
	}
	if (!(line[0] == 'x' || line[0] == 'y' || line[0] == 'z')
			|| !(line[1] == ' ' || line[1] == '\t'))
		printf("invalid arguments to cmd\n");
	basis_rot = axis - 'x';
	line = skip_spaces(line);
	angle = ft_atof_minirt(&line, error);
	if (error == EXPECTED_NUMBER)
	{
		printf("unspecified angle\n");
		return ;
	}
	if (select_type == LSC_CAMERA)
		cam_change = 1;
	rot_basis(t->rot_dir, rot);
	*(t->rot_dir) = rot_x(*(t->rot_dir), angle);
	rot_basis(t->rot_dir, -rot);
}

// end rot

void	cmd_hl(t_shell_data *t)
{
	t->hl = !(t->hl);
	// put images
}

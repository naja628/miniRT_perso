#include "shell.h"
#include <math.h>

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
	int		iaxis;
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

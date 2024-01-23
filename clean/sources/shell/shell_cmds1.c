/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmds1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:40 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:40 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	float	read_w;
	int		error;

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

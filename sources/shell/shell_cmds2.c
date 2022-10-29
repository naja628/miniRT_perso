/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cmds2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:41 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:41 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "render_scr.h"

int	cmd_h(t_shell_data *t)
{
	float	read_h;
	int		error;

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
	int		error;

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

int	cmd_ppos(t_shell_data *t)
{
	t_vec p;

	if (!(t->mv_p))
		return (printf("Nothing selected\n"));
	else
	{
		p = *(t->mv_p);
		printf("selection : element at x=%f, y=%f, z=%f\n", p.x, p.y, p.z);
	}
	return (0);
}

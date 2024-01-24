/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:39 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:39 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <poll.h>
#include "shell.h"
#include "render_scr.h"

// commands: l, s, c, n, w, h, mv, rot, render

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
}

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
#ifdef Linux
# define RCLICK 2
#else
# define RCLICK 2 
#endif

int	minirt_shell_ms_hook(int button, int x, int y, t_shell_data *t)
{
	char	*line;

	(void) x;
	(void) y;
	if (button != RCLICK)
		return (0);
	line = get_next_line(0);
	if (!line)
		return (0);
	exe_line(line, t);
	free (line);
	return (0);
}
#undef RCLICK

int minirt_shell_loop_hook(t_shell_data *t)
{
	struct pollfd in = {0, POLLIN, 0};

	poll(&in, 1, 50);
	if (in.revents & POLLIN) {
		char *line;
		line = get_next_line(0);
		exe_line(line, t);
		free(line);
	}
	return (0);
}

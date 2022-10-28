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
#define LCLICK 1

int	minirt_shell_hook(int button, int x, int y, t_shell_data *t)
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

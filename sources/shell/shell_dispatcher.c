#include "shell.h"

static void	init_dispatch(t_dispatch *t, char *cmd, t_cmd fun)
{
	t->cmd = cmd;
	t->fun = fun;
}

#define NCMD 9

t_dispatch	*dispatch_table(void)
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

int	dispatch(char *line, t_shell_data *t)
{
	int			i;
	int			cmd_len;
	t_dispatch	*table;

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

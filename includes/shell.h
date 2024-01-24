/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:36:07 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:39:51 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "parsing.h"
# include "vec.h"
# include "shape.h"
# include "render.h"
# include "scr.h"

typedef enum e_lsc
{
	LSC_LIGHT,
	LSC_CAMERA,
	LSC_SHAPE
}			t_lsc;

typedef struct s_shell_data
{
	t_parse			*data;
	t_lsc			select_type;
	t_vec			*rot_dir;
	t_vec			*mv_p;
	float			*h;
	float			*w;
	t_shape_list	*its;
	t_light_list	*itl;
	char			*args_line;
	t_scr			*scr;
}	t_shell_data;

// pointers
void		null_pointers(t_shell_data *t);
void		set_pointers(t_shell_data *t);
void		init_shell_data(t_shell_data *t, t_parse *data, t_scr *scr);

// cmds
int			cmd_l(t_shell_data *t);
int			cmd_s(t_shell_data *t);
int			cmd_c(t_shell_data *t);
int			cmd_n(t_shell_data *t);
int			cmd_w(t_shell_data *t);
int			cmd_h(t_shell_data *t);
int			cmd_mv(t_shell_data *t);
int			cmd_render(t_shell_data *t);
int			cmd_rot(t_shell_data *t);
int			cmd_ppos(t_shell_data *t);

// dispatcher
typedef int	(*t_cmd)(t_shell_data *);
typedef struct s_dispatch
{
	char	*cmd;
	t_cmd	fun;
}				t_dispatch;

t_dispatch	*dispatch_table(void);
int			dispatch(char *line, t_shell_data *t);

// hook
void		exe_line(char *line, t_shell_data *t);
int			minirt_shell_ms_hook(int button, int x, int y, t_shell_data *t);
int			minirt_shell_loop_hook(t_shell_data *t);

#endif

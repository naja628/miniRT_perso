#ifndef CLEANUP_H
# define CLEANUP_H

# include "scr.h"
# include "render.h"

typedef struct s_mem
{
	t_scene			*scene;
	t_scr			*scr;
}	t_mem;
// 	t_bump_array	*bump_maps; // TODO maybe add this field (reuse bumps etc)

int		ft_quit(t_mem *mem);
int		ft_esc_exit_hook(int keycode, t_mem *mem);
void	ft_free_lights(t_light_list *lights);
void	ft_free_shapes(t_shape_list *shapes);

#endif

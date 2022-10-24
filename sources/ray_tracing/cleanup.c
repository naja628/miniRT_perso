#include <stdlib.h>
#include "cleanup.h"
#include "mlx.h"
#include "bump_mapping.h"

void	ft_free_shapes(t_shape_list *shapes)
{
	if (!shapes)
		return ;
	else
	{
		ft_free_shapes(shapes->next);
		free(shapes->shape.data);
		// TODO is the list the handler of the bump_maps?
		if (shapes->shape.bump_map)
		{
			free(shapes->shape.bump_map->data);
			free(shapes->shape.bump_map);
		}
		free(shapes);
	}
}

void	ft_free_lights(t_light_list *lights)
{
	if (!lights)
		return ;
	else
	{
		ft_free_lights(lights->next);
		free(lights);
	}
}

// can be passed to mlx_hook (reminder destroy_notify = 17)
int	ft_quit(t_mem *mem)
{
// 	ft_free_shapes(mem->scene->shapes);
// 	ft_free_lights(mem->scene->lights);
// 	ft_free_bump_array(mem->bump_maps);
	mlx_destroy_window(mem->scr->mlx, mem->scr->win);
	mlx_destroy_image(mem->scr->mlx, mem->scr->imptr);
	exit(0);
}

#define ESC 65307 // Linux
// #define ESC 53 // MAC

// meant to be passed to mlx_key_hook
int	ft_esc_exit_hook(int keycode, t_mem *mem)
{
	if (keycode == ESC)
		ft_quit(mem);
	return (0);
}
#undef ESC

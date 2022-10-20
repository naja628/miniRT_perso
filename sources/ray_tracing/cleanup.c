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

// TODO below : maybe don't and just malloc same thing
// // TODO for bump_mapping maybe *require* a line
// // B n file1.xpm, ... , file_n.xpm
// // that way we can create all bump_maps at once
// // provide index in table as optional argument instead of file
// typedef struct s_bump_array
// {
// 	t_normals	*array;
// 	size_t		n;
// }	t_bump_array;
// 
// void ft_free_bump_array(t_bump_array *it)
// {
// 	size_t	i;
// 
// 	i = 0;
// 	while (i < it->n)
// 		free((it->array)[i++]->data);
// 	free(it->array);
// }

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

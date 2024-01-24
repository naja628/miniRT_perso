/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:44:45 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/29 14:40:28 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "render_scr.h"
#include "scr.h"
#include "camera.h"
#include "shell.h"
#include "color.h"

void	first_render(t_parse *intel, t_camera *cam, t_scr *scr)
{
	printf("rendering...\n");
	ft_render_scr(scr, cam, &(intel->scene));
	mlx_put_image_to_window(scr->mlx, scr->win, scr->imptr, 0, 0);
	printf("done\n");
}

#define QUIT_EVENT 17

//mlx_mouse_hook(scr->win, minirt_shell_hook, sh_data);
static void	launch_mlx(t_scr *scr, t_shell_data *sh_data, t_mem *mem)
{
	mlx_loop_hook(scr->mlx, minirt_shell_loop_hook, sh_data);
	mlx_key_hook(scr->win, ft_esc_exit_hook, mem);
	mlx_hook(scr->win, QUIT_EVENT, 0, ft_quit, mem);
	mlx_loop(scr->mlx);
}

#undef QUIT_EVENT

// cam is a pointer because it needs to be the same as the one
// in intel (which we pass to the shell);
int	main(int ac, char **av)
{
	t_parse			intel;
	t_scr			scr;
	t_camera		*cam;
	t_mem			mem;
	t_shell_data	sh_data;

	if (ac != 2)
		error_handler(ARGUMENTS_ERR);
	if (check_extension(av[1]) != 0)
		error_handler(FILE_EXT_ERR);
	ft_init_scr(&scr, 1000, 700, "miniRT");
	init_intel(&intel);
	intel.mlx = scr.mlx;
	mem.scene = &(intel.scene);
	mem.scr = &scr;
	if (read_intel(av[1], &intel))
		ft_quit(&mem);
	ft_adjust_for_gamma(&(intel.scene));
	cam = &(intel.cam);
	ft_mk_camscreen(cam, (float) 700 / 1000);
	first_render(&intel, cam, &scr);
	init_shell_data(&sh_data, &intel, &scr);
	printf("you are in miniRT's shell. view doc.txt for list of commands\n");
	launch_mlx(&scr, &sh_data, &mem);
	return (0);
}

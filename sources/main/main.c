/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:44:45 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/28 21:22:11 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "debug.h"
#include "render_scr.h"
#include "scr.h"
#include "camera.h"
#include "shell.h"

void	norm_main(t_parse *intel, t_camera *cam,
	t_scr *scr, t_shell_data *sh_data)
{
	ft_mk_camscreen(cam, (float) 700 / 1000);
	printf("rendering...\n");
	ft_render_scr(scr, cam, &(intel->scene));
	mlx_put_image_to_window(scr->mlx, scr->win, scr->imptr, 0, 0);
	printf("done\n");
	init_shell_data(sh_data, intel, scr);
}

int	main(int ac, char **av)
{
	t_parse			intel;
	t_scr			scr;
	t_camera		cam;
	t_mem			mem;
	t_shell_data	sh_data;

	if (ac != 2)
		error_handler(MALLOC_ERR);
	if (check_extension(av[1]) != 0)
		error_handler(FILE_EXT_ERR);
	ft_init_scr(&scr, 1000, 700, "miniRT");
	init_intel(&intel);
	intel.mlx = scr.mlx;
	mem.scene = &(intel.scene);
	mem.scr = &scr;
	if (read_intel(av[1], &intel))
		ft_quit(&mem);
	cam = intel.cam;
	norm_main(&intel, &cam, &scr, &sh_data);
// 	minirt_shell(&sh_data);
	mlx_mouse_hook(scr.win, minirt_shell_hook, &sh_data);
	mlx_key_hook(scr.win, ft_esc_exit_hook, &mem);
	mlx_hook(scr.win, 17, 0, ft_quit, &mem);
	mlx_loop(scr.mlx);
	return (0);
}

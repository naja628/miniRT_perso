/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:44:45 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/25 20:43:50 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#include "debug.h"
#include "render_scr.h"
void	ft_gamma_scene(t_scene *scene);
static int ft_pixel_color(int x, int y, int scr_w, t_scene *sce, t_camera *cam);
void	ft_render_scr(t_scr *scr, t_camera *cam, t_scene *scene);
int	main(int ac, char **av)
{
	t_parse	intel;
	t_scr	scr;
	t_camera cam;
	t_mem	mem;


	init_intel(&intel);
	if (ac != 2)
		error_handler(0);
	if (check_extension(av[1]) != 0)
		error_handler(1);
	ft_init_scr(&scr, 1000, 700, "miniRT");
	intel.mlx = scr.mlx;
	read_intel(av[1], &intel);
	print_all_data(intel);

	cam = intel.cam;

	// hardcone same scene as test.rt
// 	t_light_list lights = {{ft_vec(0, 0, 3), 0.7, ft_vec(1, 1, 1)}, NULL};
// 	t_sphere sp = {ft_vec(0, 0, 0), 1};
// 	t_shape_list	shapes = {{SHP_SPHERE, &sp, ft_vec(1, 0, 0), 0, 1}, NULL};
// 	t_scene		hardsce = {0.2, ft_vec(1, 1, 1), &lights, &shapes};
// 	t_camera	hardcam;
// 	ft_init_camera(&hardcam, ft_vec(0, -5, 0), ft_vec(0, 1, 0), 70);
// 	ft_mk_camscreen(&hardcam, (float) 700 / 1000);

	ft_mk_camscreen(&cam, (float) 700 / 1000);
	ft_render_scr(&scr, &cam, &(intel.scene));
	mlx_put_image_to_window(scr.mlx, scr.win, scr.imptr, 0, 0);
	printf("done\n"); // TODO (is printf allowed??)
	mem.scene = &(intel.scene);
	mem.scr = &scr;
	mlx_key_hook(scr.win, ft_esc_exit_hook, &mem);
	mlx_hook(scr.win, 17, 0, ft_quit, &mem);
	mlx_loop(scr.mlx);
	return (0);
}

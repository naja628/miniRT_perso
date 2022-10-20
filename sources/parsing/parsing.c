/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:17:08 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/20 19:10:21 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "debug.h"

void	init_intel(t_parse *intel)
{
	intel->error = 0;
	intel->scene.lights = NULL;
	intel->scene.shapes = NULL;
}

t_parse	read_intel(char *av)
{
	t_parse	intel;
	int		exit_code;

	init_intel(&intel);
	exit_code = 0;
	intel.fd = open(av, O_RDONLY);
	if (intel.fd == -1)
		error_handler(2);
	while (19)
	{
		intel.line = get_next_line(intel.fd);
		if (!intel.line)
		{
			free(intel.line);
			break ;
		}
		exit_code = read_id(&intel);
		free(intel.line);
		if (exit_code == 1)
			break ;
	}
	close(intel.fd);
	if (exit_code == 1)
		exit(EXIT_FAILURE);
	return (intel);
}

int	check_extension(char *file)
{
	int	count;

	count = 0;
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL)
		return (1);
	if (file[ft_strlen(file) - 1] != 't' || file[ft_strlen(file) - 2] != 'r'
		|| file[ft_strlen(file) - 3] != '.')
		return (1);
	return (0);
}

void	print_all_data(t_parse intel)
{
	print_vec("cam viewpoint", intel.cam.viewpoint);
	print_vec("cam dir", intel.cam.dir);
	printf("cam fov %d\n", intel.cam.fov_deg);
	print_vec("light pos", intel.scene.lights->light.pos);
	print_vec("light color", intel.scene.lights->light.color);
	printf("light intensity %f\n", intel.scene.lights->light.intensity);
	printf("ambient %f\n", intel.scene.ambient);
	print_vec("ambient color", intel.scene.ambient_color);
	printf("shape type = %d\n", intel.scene.shapes->shape.type);
	print_vec("shape color", intel.scene.shapes->shape.color);
	// print_vec("shape center", (t_sphere *)intel.scene.shapes->shape.data.center);
}

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
	intel = read_intel(av[1]);
	print_all_data(intel);

	cam = intel.cam;
	ft_init_scr(&scr, 1000, 700, "miniRT");

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:48 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:53:05 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "scr.h"
# include "render.h"

typedef struct s_mem
{
	t_scene			*scene;
	t_scr			*scr;
}	t_mem;

int		ft_quit(t_mem *mem);
int		ft_esc_exit_hook(int keycode, t_mem *mem);
void	ft_free_lights(t_light_list *lights);
void	ft_free_shapes(t_shape_list *shapes);

#endif

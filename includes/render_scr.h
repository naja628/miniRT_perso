/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scr.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:36:01 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:39:19 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SCR_H
# define RENDER_SCR_H

# include "camera.h"
# include "scr.h"
# include "render.h"

void	ft_render_scr(t_scr *scr, t_camera *cam, t_scene *scene);

#endif

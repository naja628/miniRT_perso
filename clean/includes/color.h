/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:49 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:01:49 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "render.h"

void	ft_gamma_correct(t_vec *rgb);
int		ft_vrgb_to_int(t_vec rgb);
t_vec	ft_color_vec(int color);
void	ft_adjust_for_gamma(t_scene *scene);

#endif

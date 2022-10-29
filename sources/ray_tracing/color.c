/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:01:17 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:46:35 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utypes.h"
#include "vec.h"
#include "color.h"

static float	ft_zero_to_one(float x)
{
	if (x < 0)
		return (0);
	else if (x > 1)
		return (1);
	else
		return (x);
}

void	ft_gamma_correct(t_vec *rgb)
{
	rgb->x = sqrt(rgb->x);
	rgb->y = sqrt(rgb->y);
	rgb->z = sqrt(rgb->z);
}

int	ft_vrgb_to_int(t_vec rgb)
{
	t_uchar	r;
	t_uchar	g;
	t_uchar	b;
	int		rgb_int;

	r = (float) ft_zero_to_one(rgb.x) * 0xff;
	g = (float) ft_zero_to_one(rgb.y) * 0xff;
	b = (float) ft_zero_to_one(rgb.z) * 0xff;
	rgb_int = 0;
	rgb_int |= r << 16;
	rgb_int |= g << 8;
	rgb_int |= b;
	return (rgb_int);
}

t_vec	ft_color_vec(int color)
{
	t_vec	vrgb;

	vrgb.x = ((color & 0xff0000) >> 16) / (float) 255;
	vrgb.y = ((color & 0xff00) >> 8) / (float) 255;
	vrgb.z = (color & 0xff) / (float) 255;
	return (vrgb);
}

// tries to make so color and intensities are consistent with and without
// gamme correction
void	ft_adjust_for_gamma(t_scene *sce)
{
	t_shape_list	*its;
	t_light_list	*itl;
	t_vec			*color;

	sce->ambient *= sce->ambient;
	sce->ambient_color = ft_vec_mult(sce->ambient_color, sce->ambient_color);
	itl = sce->lights;
	while (itl)
	{
		color = &(itl->light.color);
		*color = ft_vec_mult(*color, *color);
		itl = itl->next;
	}
	its = sce->shapes;
	while (its)
	{
		color = &(its->shape.color);
		*color = ft_vec_mult(*color, *color);
		its = its->next;
	}
}

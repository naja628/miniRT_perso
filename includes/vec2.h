/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:36:11 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:36:11 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

// 2d point type 
// (used to represent a point as seen from within a 3d surface,
// eg, for bump-mapping)
typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:35:48 by najacque          #+#    #+#             */
/*   Updated: 2022/10/29 14:35:48 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include "vec.h"

typedef struct s_line
{
	t_vec	p;
	t_vec	dir;
}	t_line;

t_vec	ft_point_at_t(t_line *line, float t);

#endif

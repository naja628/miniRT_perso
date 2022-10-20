/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:24:32 by xle-boul          #+#    #+#             */
/*   Updated: 2022/09/26 20:26:53 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_array_of_strings(char **in_line)
{
	int	i;

	i = 0;
	while (in_line[i] != NULL)
		i++;
	while (i >= 0)
	{
		free (in_line[i]);
		i--;
	}
	free (in_line);
}

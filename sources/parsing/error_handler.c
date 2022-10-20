/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:44:11 by xle-boul          #+#    #+#             */
/*   Updated: 2022/09/26 21:01:57 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	error_handler(int error)
{
	if (error == 0)
		printf("Error!\nWrong number of arguments\n");
	else if (error == 1)
		printf("Error!\nFile extension must be .rt\n");
	else if (error == 2)
		printf("Error!\nCould not read file\n");
	else if (error == 3)
		printf("Error!\nWrong number of arguments\n");
	else if (error == 4)
		printf("Error!\nWrong number of arguments\n");
	exit(EXIT_FAILURE);
}

int	error_handler_free(int error, char **in_line, t_parse *intel)
{
	if (error == 0)
		printf("Error!\nMachin qui free\n");
	else if (error == 1)
		printf("Error!\nFile extension must be .rt\n");
	else if (error == 2)
		printf("Error!\nCould not read file\n");
	else if (error == 3)
		printf("Error!\nWrong number of arguments\n");
	else if (error == 4)
		printf("Error!\nWrong number of arguments\n");
	if (in_line != NULL)
		free_array_of_strings(in_line);
	// if (intel->all.lights != NULL)
	// 	free_list(intel->all.lights);
	// if (intel->all.shapes != NULL)
	// 	free_list(intel->all.shapes);
	exit(EXIT_FAILURE);
}

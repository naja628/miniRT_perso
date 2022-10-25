/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:44:11 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/25 22:34:53 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	error_handler(int error)
{
	if (error == MALLOC_ERR)
		printf("Error!\nMalloc failed\n");
	else if (error == FILE_EXT_ERR)
		printf("Error!\nFile extension must be .rt\n");
	else if (error == READ_FILE_ERR)
		printf("Error!\nCould not read file\n");
	else if (error == INVALID_DATA_ERR)
		printf("Error!\nData provided is corrupted\n");
	else if (error == ARGUMENTS_ERR)
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

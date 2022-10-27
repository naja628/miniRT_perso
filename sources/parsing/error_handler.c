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

void print_error(int error, char *line)
{
	if (!error)
		return ;
	// TODO ideally we need dprintf(2, ...) but not allowed (??)
	printf("Error\n");
	if (line)
		printf("On line: %s", line);
	// line
	if (error == COMMA_SEP)
		printf("Expected comma\n");
	else if (error == TRAILING_CHARS)
		printf("Trailings chars\n");
	else if (error == WRONG_VALUE || error == DIR_NOT_UNIT)
		printf("Invalid argument\n");
	else if (error == EXPECTED_NUMBER)
		printf("Expected number\n");
	else if (error == UNKNOWN_ID)
		printf("Unknow identifier at start of line\n");
	else if (error == MALLOC_ERR)
		printf("Bad alloc. Are you out of RAM?\n");
	else if (error == XPM_READ)
		printf("Failed to read xpm. Expected ... <valid_xpm> <map_height>\n");
	// no line
	else if (error == READ_FILE_ERR)
		printf("Could not open .rt file\n");
	else if (error == NOT_ONE_CAM)
		printf("Must define camera exactly once\n");
	else if (error == NOT_ONE_AMBIENT)
		printf("Must define ambient light exactly once\n");
}
	
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
	(void) intel; // compile with warnings (TODO why did we need it?)
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

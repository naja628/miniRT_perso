/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:44:11 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 22:44:31 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_error(int error, char *line)
{
	if (!error)
		return ;
	printf("Error\n");
	if (line)
		printf("On line: %s", line);
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

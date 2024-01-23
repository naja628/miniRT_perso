/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:44:11 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/29 13:55:13 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_error(int error, char *line)
{
	if (!error)
		return ;
	dprintf(2, "Error\n");
	if (line)
		dprintf(2, "On line: %s", line);
	if (error == COMMA_SEP)
		dprintf(2, "Expected comma\n");
	else if (error == TRAILING_CHARS)
		dprintf(2, "Trailings chars\n");
	else if (error == WRONG_VALUE || error == DIR_NOT_UNIT)
		dprintf(2, "Invalid argument\n");
	else if (error == EXPECTED_NUMBER)
		dprintf(2, "Expected number\n");
	else if (error == UNKNOWN_ID)
		dprintf(2, "Unknow identifier at start of line\n");
	else if (error == MALLOC_ERR)
		dprintf(2, "Bad alloc. Are you out of RAM?\n");
	else if (error == XPM_READ)
		dprintf(2, "Failed to read xpm. Expected... <valid_xpm> <map_height>\n");
	else if (error == READ_FILE_ERR)
		dprintf(2, "Could not open .rt file\n");
	else if (error == UNIQUE_ELEM)
		dprintf(2, "Unique elements must be defined exactly once\n");
}

int	error_handler(int error)
{
	if (error == MALLOC_ERR)
		dprintf(2, "Error!\nMalloc failed\n");
	else if (error == FILE_EXT_ERR)
		dprintf(2, "Error!\nFile extension must be .rt\n");
	else if (error == READ_FILE_ERR)
		dprintf(2, "Error!\nCould not read file\n");
	else if (error == INVALID_DATA_ERR)
		dprintf(2, "Error!\nData provided is corrupted\n");
	else if (error == ARGUMENTS_ERR)
		dprintf(2, "Error!\nWrong number of arguments\n");
	exit(EXIT_FAILURE);
}

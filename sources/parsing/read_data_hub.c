/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data_hub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:03:04 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 22:57:00 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "debug.h"

// TODO copy line and send it to functions in order to check the end of the line
// after use: (line **)
// if (*line == '\n')
// intel->error = 2;

// returns 1 if line begins with id
int	id_match(char *linestart, char *id, size_t id_len)
{
	char	after;

	// TODO problem if line shorter than id
	if (ft_strlen(linestart) < id_len)
		return (0);
	after = linestart[id_len];
	if (!ft_strncmp(linestart, id, id_len) 
		&& (after == ' ' || after == '\t' || after == '\n' || after == '\0'))
		return (1);
	else
		return (0);
}

// gestion erreurs: int tous les read. return code d'erreur.
// si code d'erreur, read_id return le code et on l'interprete dans read_intel
// warnings:
//	in bonus

// fatal errors:
//	in base version

int	read_id_shapes(t_parse *intel)
{
	if (id_match(intel->line, SPHERE, 2))
		return (read_shape(intel, (intel->line + 2), read_sphere, SHP_SPHERE));
	else if (id_match(intel->line, CYLINDER, 2))
		return (read_shape(intel, (intel->line + 2), read_cylinder, SHP_CYLIN));
	else if (id_match(intel->line, PLANE, 2))
		return (read_shape(intel, (intel->line + 2), read_plane, SHP_PLANE));
	else if (id_match(intel->line, CONE, 2))
		return (read_shape(intel, (intel->line + 2), read_cone, SHP_CONE));
	return (0);
}

int	read_id(t_parse *intel)
{
	if (id_match(intel->line, AMBIENT_LIGHT, 1))
	{
		intel->num_ambients++;
		return (read_ambient_light(intel, (intel->line + 1)));
	}
	else if (id_match(intel->line, CAMERA, 1))
	{
		intel->num_cameras++;
		return (read_camera(intel, (intel->line + 1)));
	}
	else if (id_match(intel->line, LIGHT, 1))
	{
		intel->num_lights++;
		return (read_light(intel, (intel->line + 1)));
	}
	else if (id_match(intel->line, SPHERE, 2)
		|| id_match(intel->line, CYLINDER, 2)
		|| id_match(intel->line, PLANE, 2)
		|| id_match(intel->line, CONE, 2))
		return (read_id_shapes(intel));
	else if (!(ft_strncmp(intel->line, COMMENT, 1) == 0))
		return (UNKNOWN_ID);
	return (0);
}

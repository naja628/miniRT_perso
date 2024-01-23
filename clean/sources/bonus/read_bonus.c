/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:28:22 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 22:48:57 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*copy_xpm(char **line, int len)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = malloc(sizeof(char) * len + 1);
	if (!file_name)
		return (NULL);
	while (i < len)
	{
		file_name[i] = *(*line);
		(*line)++;
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}

int	file_name_length(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != ' ' && line[1] != '\n' && line[1] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	check_xpm(char *file_name, int *ret)
{
	int	len;

	if (!file_name)
	{
		*ret = MALLOC_ERR;
		return (1);
	}
	len = ft_strlen(file_name);
	if (ft_strncmp(file_name + len - 4, ".xpm", 4))
	{
		printf("%s not .xpm\n", file_name + len - 6);
		*ret = XPM_READ;
		return (1);
	}
	return (0);
}

// EXPECTED_NUMBER is ok here
static int	read_xpm(char *line, t_shape_list *new, void *mlx, int *ret)
{
	char		*file_name;
	t_normals	*map;

	if (*ret)
		return (*ret);
	map = malloc(sizeof(t_normals));
	if (!map)
		return (MALLOC_ERR);
	file_name = copy_xpm(&line, file_name_length(line));
	if (check_xpm(file_name, ret) == 0)
		*ret = ft_xpm_to_normals(mlx, map, file_name, 0.05);
	free(file_name);
	line = skip_spaces(line);
	new->shape.map_height = ft_atof_minirt(&line, ret);
	want_positive(new->shape.map_height, ret);
	if (!(*ret))
		new->shape.bump_map = map;
	else
	{
		free(map);
		return (XPM_READ);
	}
	return (eol_checker(&line) * TRAILING_CHARS);
}

int	read_bonus(char *line, t_shape_list *new, void *mlx, int *ret)
{
	if (*ret)
		return (*ret);
	line = skip_spaces(line);
	new->shape.dif_coef = ft_atof_minirt(&line, ret);
	line = skip_spaces(line);
	new->shape.spec_coef = ft_atof_minirt(&line, ret);
	line = skip_spaces(line);
	new->shape.refl_coef = ft_atof_minirt(&line, ret);
	want_coefs(&(new->shape), ret);
	line = skip_spaces(line);
	new->shape.is_checkered = ft_atoi_minirt(&line, ret);
	want_bool(new->shape.is_checkered, ret);
	if ((*ret == EXPECTED_NUMBER || *ret == 0) && eol_checker(&line) == 0)
		return (0);
	else
		return (read_xpm(line, new, mlx, ret));
}

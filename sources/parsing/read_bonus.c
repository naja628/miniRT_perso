/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:28:22 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/26 23:14:05 by xle-boul         ###   ########.fr       */
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
		error_handler(MALLOC_ERR);
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
	if (ft_strnstr(file_name, ".xpm", ft_strlen(file_name)) == NULL)
		return (1);
	if (file_name[ft_strlen(file_name) - 1] != 'm'
		|| file_name[ft_strlen(file_name) - 2] != 'p'
		|| file_name[ft_strlen(file_name) - 3] != 'x'
		|| file_name[ft_strlen(file_name) - 4] != '.')
	{
		*ret = WRONG_VALUE;
		return (1);
	}
	return (0);
}


// check if value of the 3 coefs <= 1

void	read_bonus(char *line, t_shape_list *new, void *mlx, int *ret)
{
	char		*file_name;
	t_normals	*map;

	line = skip_spaces(line);
	new->shape.dif_coef = ft_atof_minirt(&line, ret);
	line = skip_spaces(line);
	new->shape.spec_coef = ft_atof_minirt(&line, ret);
	line = skip_spaces(line);
	new->shape.refl_coef = ft_atof_minirt(&line, ret);
	line = skip_spaces(line);
	new->shape.is_checkered = ft_atoi_minirt(&line, ret);
	if (eol_checker(&line) == 0)
		return ;
	map = malloc(sizeof(t_normals));
	if (!map)
		error_handler(MALLOC_ERR);
	file_name = copy_xpm(&line, file_name_length(line));
	line = skip_spaces(line);
	new->shape.map_height = ft_atof_minirt(&line, ret);
	if (check_xpm(file_name, ret) == 0)
	{
		ft_xpm_to_normals(mlx, map, file_name, 0.05);
		new->shape.bump_map = map;
	}
	free(file_name);
}

// int	read_bonus(char *line, t_shape_list *new, void *mlx)
// {
// 	char		*file_name;
// 	t_normals	*map;
// 
// 	line = skip_spaces(line);
// 	new->shape.dif_coef = ft_atof_minirt(&line);
// 	printf("shape %f\n", new->shape.dif_coef);
// 	line = skip_spaces(line);
// 	new->shape.spec_coef = ft_atof_minirt(&line);
// 	line = skip_spaces(line);
// 	new->shape.refl_coef = ft_atof_minirt(&line);
// 	line = skip_spaces(line);
// 	new->shape.is_checkered = ft_atoi_minirt(&line, &ret);
// 	if (eol_checker(&line) == 0)
// 		return (0);
// 	printf("rb0\n");
// 	map = malloc(sizeof(t_normals));
// 	if (!map)
// 		error_handler(0);
// 	printf("map %p\n", map);
// 	file_name = copy_xpm(&line, file_name_length(line));
// 	printf("file name = _%s_\n", file_name);
// 	line = skip_spaces(line);
// 	new->shape.map_height = ft_atof_minirt(&line);
// 	if (check_xpm(file_name) == 0)
// 	{
// 		printf("rb1\n");
// 		// printf("scanned correctly\n");
// 		printf("err %d", ft_xpm_to_normals(mlx, map, file_name, 0.05));
// 		new->shape.bump_map = map;
// 		printf("rb2\n");
// 	}
// 	free(file_name);
// 	//mlx has to arrive here ^
// 	return (0);
// }

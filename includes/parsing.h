/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:17:35 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/24 18:12:44 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line_bonus.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "camera.h"
# include "render.h"
# include "shape.h"
# include "vec.h"
# include "math_utils.h"
# include "scr.h"
# include "line.h"
# include "mlx.h" // ok because -I sources/mlx_linux should find it
# include "cleanup.h"

# define AMBIENT_LIGHT "A"
# define CAMERA "C"
# define LIGHT "L"
# define SPHERE "sp"
# define PLANE "pl"
# define CYLINDER "cy"
# define CONE "cn"

/*	id		name				extensions
	A		ambiant light		ambiant + colors
	C		camera				coord xyz + vector (orientation) + FOV
	L		light				coord xyz + ratio brightness + (bonus) color
	sp		sphere				coord xyz + diameter (!ray) + color
	pl		plane				coord xyz + vector (orientation) + color
	cy		cylinder			coord xyz + vector (orientation) + diameter + hight + color
*/
typedef struct s_parse
{
	int			error;
	t_camera	cam;
	t_scene		scene;
	int			fd;
	char		*line;
	void		*mlx;
}				t_parse;
/*
	error codes:
					1: comma separator
					2: unwanted chars at the end of line
					3: invalid domain
					4: dir not unit
*/

typedef void	*(*t_read)(t_parse *, char **);

// error handling

int		error_handler(int error);
int		error_handler_free(int error, char **in_line, t_parse *intel);

// utilities

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
char	*skip_spaces(char *line);
int		ft_atoi_minirt(char **str);
float	ft_atof_minirt(char **str);

// parsing

void	print_all_data(t_parse intel);
int		check_extension(char *file);
t_parse	read_intel(char *av);
void	init_intel(t_parse *intel);

// data handling

int		read_id(t_parse *intel);
void	assign_intel(t_parse *intel, char **in_line);
void	*read_plane(t_parse *intel, char **line);
void	*read_cylinder(t_parse *intel, char **line);
void	*read_sphere(t_parse *intel, char **line);
void	*read_cone(t_parse *intel, char **line);
void	read_shape(t_parse *intel, char *line, t_read fun, t_shapetype type);
void	read_light(t_parse *intel, char *line);
void	read_camera(t_parse *intel, char *line);
void	read_ambient_light(t_parse *intel, char *line);

// free stuff

void	free_array_of_strings(char **in_line);

#endif

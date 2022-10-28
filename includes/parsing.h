/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:17:35 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/28 23:10:49 by xle-boul         ###   ########.fr       */
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
# define COMMENT "#"
// use '#' instead of '//' as comment out symbol bc norminette dislikes '//' 

// Error codes in parsing
# define READ_FILE_ERR 2
# define INVALID_DATA_ERR 3
# define ARGUMENTS_ERR 4

// Error codes in read
# define COMMA_SEP 1
# define TRAILING_CHARS 2
# define WRONG_VALUE 3
# define DIR_NOT_UNIT 4
# define EXPECTED_NUMBER 5
# define UNKNOWN_ID 6
# define MALLOC_ERR 7
# define FILE_EXT_ERR 8
# define NOT_ONE_CAM 9
# define NOT_ONE_AMBIENT 10
# define XPM_READ 11
# define MISSING_NUMBER 12
# define NOT_ONE_LIGHT 13

typedef struct s_parse
{
	int			error;
	t_camera	cam;
	t_scene		scene;
	int			fd;
	char		*line;
	void		*mlx;
	int			num_cameras;
	int			num_ambients;
	int			num_lights;
}				t_parse;

typedef void	*(*t_read)(char **, int *);

// error handling

void	print_error(int error, char *line);
int		error_handler(int error);

// utilities

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char	**ft_split(char const *s, char c);
char	*skip_spaces(char *line);
int		ft_atoi_minirt(char **str, int *ret);
float	ft_atof_minirt(char **str, int *ret);
int		id_match(char *linestart, char *id, size_t id_len);

// parsing

int		cam_and_ambient_once(t_parse *intel, int *error);
void	print_all_data(t_parse intel);
int		check_extension(char *file);
int		read_intel(char *av, t_parse *intel);
void	init_intel(t_parse *intel);

// data handling

int		read_id(t_parse *intel);
void	assign_intel(t_parse *intel, char **in_line);
void	*read_plane(char **line, int *ret);
void	*read_cylinder(char **line, int *ret);
void	*read_sphere(char **line, int *ret);
void	*read_cone(char **line, int *ret);
int		read_shape(t_parse *intel, char *line, t_read fun, t_shapetype type);
int		read_light(t_parse *intel, char *line);
int		read_camera(t_parse *intel, char *line);
int		read_ambient_light(t_parse *intel, char *line);
int		read_bonus(char *line, t_shape_list *new, void *mlx, int *ret);

// data utilities

t_vec	read_color(char **line, int *error);
t_vec	read_vec(char **line, int *error);
int		eol_checker(char **line);

// data validation

int		want_bool(int boolean, int *berr);
int		want_positive(float x, int *berr);
int		want_ratio(float ratio, int *berr);
int		want_unit(t_vec	unit, int *berr);
int		set_if_zero(int *berr, int new_err);
int		want_coefs(t_shape *s, int *berr);

#endif

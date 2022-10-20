#ifndef BUMP_MAPPING_H
# define BUMP_MAPPING_H

typedef struct s_imdata
{
	int		w;
	int		h;
	char	*data;
}	t_imdata;

typedef struct s_normals
{
	int		w;
	int		h;
	t_vec	*data;
}	t_normals;

int		ft_xpm_to_imdata(void *mlx, char *filename, t_imdata *buff);
void	ft_mk_normal_map(t_normals *map, t_imdata *heights, float maxh);
int		ft_xpm_to_normals(void *mlx, t_normals *map, char *fn, float maxh);

#endif

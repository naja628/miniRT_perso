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

# define E_LOADING 1
# define E_NOT32 2

int		ft_xpm_to_imdata(void *mlx, char *fn, t_imdata *buff, void **delme);
void	ft_mk_normal_map(t_normals *map, t_imdata *heights, float maxh);

// read xpm file 'fn' (as a height map) and fill t_normals struct map
// with the corresponding data
// mlx the mlx pointer, and maxh is controls how accentuated the heights are
// return error code: 
// 	0 if ok
// 	1=E_LOADING if error loading file
// 	2=E_NOT32 if native color format not supported
int		ft_xpm_to_normals(void *mlx, t_normals *map, char *fn, float maxh);

#endif

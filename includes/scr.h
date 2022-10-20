#ifndef SCR_H
# define SCR_H

# include "utypes.h"

typedef struct s_scr
{
	t_uint	w;
	t_uint	h;
	void	*mlx;
	void	*win;
	void	*imptr;
	char	*data;
	int		bits;
	int		line_sz;
	int		bigend;
}	t_scr;

void	ft_init_scr(t_scr *scr, t_uint w, t_uint h, char *winname);
void	ft_pixel_to_scr(t_scr *img, int x, int y, int rgb);

#endif

#ifndef CAMERA_H
# define CAMERA_H

# include "scr.h"
# include "vec.h"
# include "line.h"

typedef struct s_camera
{
	t_vec	corner;
	t_vec	viewpoint;
	t_vec	dir;
	t_vec	hz_dir;
	t_vec	vt_dir;
	int		fov_deg;
}	t_camera;

void	ft_init_camera(t_camera *cam, t_vec vp, t_vec dir, int fov_deg);
void	ft_mk_camscreen(t_camera *cam, float ratio);
void	ft_ray(t_line *ray, float x, float y, t_camera *cam);

#endif

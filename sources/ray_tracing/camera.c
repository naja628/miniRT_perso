#include <math.h>
#include "vec.h"
#include "camera.h"
#include "mlx.h"
#include "bases.h"
#include "math_utils.h"

// This line bad because gets mlx from system instead of our repo
// # include <mlx.h>
// Are these really needed? 
// # include <sys/mman.h>
// # include <X11/Xlib.h>
// # include <X11/Xutil.h>
// # include <sys/ipc.h>
// # include <sys/shm.h>
// # include <X11/extensions/XShm.h>
// # include <X11/XKBlib.h>

// init a camera screen
// note : after using this function 'cam' won't be in a usable state yet
// 'ft_mk_camscreen' needs to be called so we know where the corner
// of the "virtual screen" is
void	ft_init_camera(t_camera *cam, t_vec vp, t_vec dir, int fov_deg)
{
	cam->dir = dir;
	cam->fov_deg = fov_deg;
	cam->viewpoint = vp;
}

void	ft_mk_camscreen(t_camera *c, float ratio)
{
	float		d;
	float		fov;
	const float	eps = 0.001;

	fov = M_PI * c->fov_deg / 180;
	d = 1 / (2 * tan(fov / 2));
	if (ft_colin(c->dir, ft_vec(0, 0, 1)))
		ft_complete_basis(c->dir, ft_vec(0, -1, 0), &c->hz_dir, &c->vt_dir);
	else
		ft_complete_basis(c->dir, ft_vec(0, 0, 1), &c->hz_dir, &c->vt_dir);
	c->corner = ft_vec_add(ft_scaled(d, c->dir), ft_scaled(-0.5, c->hz_dir));
	c->corner = ft_vec_add(c->corner, ft_scaled(-0.5 * ratio, c->vt_dir));
}

void	ft_ray(t_line *ray, float x, float y, t_camera *cam)
{
	ray->p = cam->viewpoint;
	ray->dir = ft_vec_add(cam->corner, ft_scaled(x, cam->hz_dir));
	ray->dir = ft_vec_add(ray->dir, ft_scaled(y, cam->vt_dir));
	ft_make_unit(&ray->dir);
}

#include "render_scr.h"
#include "vec.h"
#include "vec2.h"
#include "camera.h"
#include "scr.h"
#include "render.h"
#include "color.h"
#include "utypes.h"

// if the camera "virtual" screen corresponds to 'scr'
// find the coordinates of pixel x, y on the virtual screen
// (as t_vec2)
static t_vec2	ft_pix_center(int x, int y, t_scr *scr)
{
	t_vec2	ret;

	ret.x = (float) x / (scr->w - 1);
	ret.y = (float) y / (scr->w - 1);
	return (ret);
}

// scattered *shall* be an valid array of 4 (uninitialzed) 2d points.
// fill it with the corners of the square with center 'center' and 
// side 'dvg'
static void	ft_scatter4(t_vec2 *scattered, t_vec2 center, float dvg)
{
	const float	xs[4] = {-0.5, 0.5, -0.5, 0.5};
	const float	ys[4] = {-0.5, -0.5, 0.5, 0.5};
	int			i;

	i = 0;
	while (i < 4)
	{
		scattered[i].x = center.x + dvg * xs[i];
		scattered[i].y = center.y + dvg * ys[i];
		++i;
	}
}

#define BOUNCES 5
#define MIN_RATIO 0.05
// 'smp' are points in the coordinates system of the camera's
// "virtual screen"
// make a ray pass through each point, and return the color that results 
// from averaging the colors of each ray (as computed by ft_ray_color)
static t_vec	ft_avg_samples(int n, t_vec2 *smp, t_camera *cam, t_scene *sce)
{
	int		i;
	t_vec	vrgb;
	t_line	ray;

	i = 0;
	vrgb = ft_vec(0, 0, 0);
	while (i < n)
	{
		ft_ray(&ray, smp[i].x, smp[i].y, cam);
		ft_add_to(&vrgb, ft_ray_color(&ray, sce, BOUNCES, 1.0 / MIN_RATIO));
		++i;
	}
	ft_scale(1.0 / n, &vrgb);
	return (vrgb);
}
#undef BOUNCES
#undef MIN_RATIO

void	ft_render_scr(t_scr *scr, t_camera *cam, t_scene *sce)
{
	t_uint	x;
	t_uint	y;
	int		color;
	t_vec2	smp[4];

	x = 0;
	y = 0;
	while (x < scr->w)
	{
		while (y < scr->h)
		{
			ft_scatter4(smp, ft_pix_center(x, y, scr), 0.5 / (scr->w - 1));
			// gamma?
			color = ft_vrgb_to_int(ft_avg_samples(4, smp, cam, sce));
			ft_pixel_to_scr(scr, x, y, color);
			++y;
		}
		y = 0;
		++x;
	}
}

#include "vec.h"
#include "line.h"

t_vec	ft_point_at_t(t_line *line, float t)
{
	return (ft_vec_add(line->p, ft_scaled(t, line->dir)));
}

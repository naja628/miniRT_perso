#ifndef LINE_H
# define LINE_H

# include "vec.h"

typedef struct s_line
{
	t_vec	p;
	t_vec	dir;
}	t_line;

t_vec	ft_point_at_t(t_line *line, float t);

#endif

#include <stdio.h>
#include "vec.h"

void	print_vec(char *name, t_vec u)
{
	printf("%s: %f %f %f\n", name, u.x, u.y, u.z);
}

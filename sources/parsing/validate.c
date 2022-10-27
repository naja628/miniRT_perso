#include "parsing.h"

int want_positive(float x, int *berr)
{
	if (*berr)
		return (*berr);
	if (x < 0.01)
		*berr = WRONG_VALUE;
	return (*berr);
}

int	want_ratio(float ratio, int *berr)
{
	if (*berr)
		return (*berr);
	if (!(0.0 <= ratio && ratio <= 1.0))
		*berr = WRONG_VALUE;
	return (*berr);
}

int	want_unit(t_vec	unit, int *berr)
{
	if (*berr)
		return (*berr);
	if (!ft_near_zero(ft_norm(unit) - 1, 0.005))
		*berr = DIR_NOT_UNIT;
	return (*berr);
}

int	set_if_zero(int *berr, int new_err)
{
	if (*berr)
		return (*berr);
	*berr = new_err;
	return (*berr);
}

int	want_coefs(t_shape *s, int *berr)
{
	if (*berr)
		return (*berr);
	if (s->dif_coef < 0 || s->spec_coef < 0 || s->refl_coef < 0
			|| s->dif_coef + s->spec_coef + s->refl_coef > 1.01)
		*berr = WRONG_VALUE;
	return (*berr);
}

int	want_bool(int boolean, int *berr)
{
	if (*berr)
		return (*berr);
	if (!(boolean == 0 || boolean == 1))
		*berr = WRONG_VALUE;
	return (*berr);
}

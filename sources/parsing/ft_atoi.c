/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:21:38 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/27 23:05:01 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parsing.h"

#include "parsing.h"
#define LL_MAX 9223372036854775807

typedef struct s_atoi
{
	int						i;
	long long				lln;
	char					*str_bis;
	int						sign;
}				t_atoi;

int	ft_atoi_minirt_loop(t_atoi *n)
{
	while (48 <= *(n->str_bis) && *(n->str_bis) <= 57)
	{
		if (n->i == 1 && (n->lln * 10 + (*(n->str_bis) - 48)) < n->lln)
			return (-1);
		if (n->i == -1 && (n->lln * 10 + (*(n->str_bis) - 48)) < n->lln)
			return (0);
		n->lln = n->lln * 10 + (*(n->str_bis) - 48);
		if (n->i == 1 && n->lln > LL_MAX)
			return (-1);
		else if (n->i == -1 && (unsigned long long)n->lln > (LL_MAX))
			return (0);
		n->str_bis++;
	}
	return ((int)n->lln * n->i);
}

int	ft_atoi_minirt(char **str, int *ret)
{
	t_atoi	n;
	int		value;

	value = 0;
	if (*ret)
		return (0);
	n.lln = 0;
	n.i = 1;
	n.str_bis = *str;
	if (!(*n.str_bis == '-') && !(48 <= *n.str_bis && *n.str_bis <= 57))
	{
		*ret = EXPECTED_NUMBER;
		return (0);
	}
	if (*n.str_bis == '-')
	{
		n.i = -1;
		n.str_bis++;
	}
	value = ft_atoi_minirt_loop(&n);
	*str = n.str_bis;
	return (value);
}

float	ft_atof_split(t_atoi *n)
{
	float	k;
	int		decimal;

	k = 0;
	decimal = 1;
	while ('0' <= *(n->str_bis) && *(n->str_bis) <= '9')
	{
		n->lln = n->lln * 10 + (*(n->str_bis) - '0');
		(n->str_bis)++;
	}
	if (*(n->str_bis) == '.')
	{
		(n->str_bis)++;
		while ('0' <= *(n->str_bis) && *(n->str_bis) <= '9')
		{
			n->lln = n->lln * 10 + (*(n->str_bis) - '0');
			decimal *= 10;
			(n->str_bis)++;
		}
	}
	n->lln *= n->i;
	k = (float)n->lln / decimal;
	return (k);
}

float	ft_atof_minirt(char **str, int *ret)
{
	t_atoi	n;
	float	k;

	if (*ret)
		return (0);
	n.lln = 0;
	n.i = 1;
	n.str_bis = (char *)*str;
	if (!(*n.str_bis == '-') && !(48 <= *n.str_bis && *n.str_bis <= 57))
	{
		*ret = EXPECTED_NUMBER;
		return (0);
	}
	if (*n.str_bis == '-')
	{
		n.i = -1;
		n.str_bis++;
	}
	k = ft_atof_split(&n);
	*str = n.str_bis;
	return (k);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 13:21:38 by xle-boul          #+#    #+#             */
/*   Updated: 2022/09/26 23:35:40by xle-boul         ###   ########.fr       */
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

typedef struct s_atof
{
	int						i;
	float					f;
	char					*str_bis;
	int						sign;
}				t_atof;
/* converts a string to corresponding integer */

// commented out : Compile with warnings (TODO do we need it or delete)
// static char	*ft_trim_string(const char *str, t_atoi *n)
// {
// 	n->sign = 0;
// 	n->i = 1;
// 	if (!str)
// 		return (0);
// 	while (*str == '\t' || *str == '\n' || *str == '\v'
// 		|| *str == '\r' || *str == '\f' || *str == ' ')
// 		str++;
// 	while (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			n->sign++;
// 		str++;
// 	}
// 	if (n->sign % 2 != 0)
// 		n->i = -1;
// 	return ((char *)str);
// }

int	ft_atoi_minirt(char **str, int *ret)
{
	t_atoi	n;

	n.lln = 0;
	n.i = 1;
	n.str_bis = *str;
	if (!(*n.str_bis != '-') && !(48 <= *n.str_bis && *n.str_bis <= 57))
	{
		*ret = WRONG_VALUE;
		return (0);
	}
	if (*n.str_bis == '-')
	{
		n.i = -1;
		n.str_bis++;
	}
	while (48 <= *n.str_bis && *n.str_bis <= 57)
	{
		if (n.i == 1 && (n.lln * 10 + (*n.str_bis - 48)) < n.lln)
			return (-1);
		if (n.i == -1 && (n.lln * 10 + (*n.str_bis - 48)) < n.lln)
			return (0);
		n.lln = n.lln * 10 + (*n.str_bis - 48);
		if (n.i == 1 && n.lln > LL_MAX)
			return (-1);
		else if (n.i == -1 && (unsigned long long)n.lln > (LL_MAX))
			return (0);
		n.str_bis++;
	}
	*str = n.str_bis;
	return ((int)n.lln * n.i);
}

float	ft_atof_minirt(char **str, int *ret)
{
	t_atoi	n;
	float	k;
	int		decimal;

	n.lln = 0;
	n.i = 1;
	decimal = 1;
	n.str_bis = (char *)*str;
	if (!(*n.str_bis == '-') && !(48 <= *n.str_bis && *n.str_bis <= 57))
	{
		*ret = WRONG_VALUE;
		printf("test success\n");
		return (0);
	}
	if (*n.str_bis == '-')
	{
		n.i = -1;
		n.str_bis++;
	}
	while ('0' <= *n.str_bis && *n.str_bis <= '9')
	{
		n.lln = n.lln * 10 + (*n.str_bis - '0');
		n.str_bis++;
	}
	if (*n.str_bis == '.')
	{
		n.str_bis++;
		while ('0' <= *n.str_bis && *n.str_bis <= '9')
		{
			n.lln = n.lln * 10 + (*n.str_bis - '0');
			decimal *= 10;
			n.str_bis++;
		}
	}
	n.lln *= n.i;
	k = (float)n.lln;
	*str = n.str_bis;
	return (((k / decimal)));
}

// int main()
// {
// 	char s[] = "928.54";
// 	char *s_bis = s;
// 	printf("%f\n", ft_atof(&s_bis));
// 	printf("%f\n", atof(s));
// 	return 0;
// }

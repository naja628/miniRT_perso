/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xle-boul <xle-boul@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 23:00:51 by xle-boul          #+#    #+#             */
/*   Updated: 2022/10/05 20:59:44 by xle-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	if (n == 0 || !s1 || !s2)
		return (0);
	while (i++ < n - 1 && *a == *b && *a != '\0' && *b != '\0')
	{
		a++;
		b++;
	}
	return (*a - *b);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	if (*little == '\0')
		return ((char *)big);
	while (len-- >= ft_strlen(little) && *big != '\0')
	{
		if (*big == *little && ft_strncmp(big, little, ft_strlen(little)) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}

char	*skip_spaces(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

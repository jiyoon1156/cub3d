/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:29:24 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 16:07:57 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_util.h"

int		ft_atoi(const char *str)
{
	int		sign;
	int		result;
	int		i;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

size_t	ft_wordcount(char const *s1, char const c)
{
	size_t	count;

	count = 0;
	while (*s1)
	{
		while (*s1 == c)
			s1++;
		if (*s1 && *s1 != c)
			count++;
		while (*s1 && *s1 != c)
			s1++;
	}
	return (count);
}

size_t	ft_checklen(char const *s1, char const c)
{
	size_t	count;

	count = 0;
	while (*s1 && *s1 != c)
	{
		count++;
		s1++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;

	result = malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (result == 0)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = malloc(sizeof(char) * (ft_checklen(s, c) + 1));
			if (result[i] == 0)
				return (0);
			j = 0;
			while (*s && *s != c)
				result[i][j++] = *s++;
			result[i][j] = '\0';
			i++;
		}
	}
	result[i] = 0;
	return (result);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && *s2 && i < n)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - *s2);
		i++;
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - *s2);
}

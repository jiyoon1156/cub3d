/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:28:09 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 18:32:45 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin_point(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(sizeof(char) * (len + 2));
	if (result == 0)
		return (0);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	result[i++] = '.';
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

void	free_info(char **info, char const *s, char c)
{
	int		n;
	int		i;

	n = ft_wordcount(s, c);
	i = 0;
	while (i < n)
	{
		free(info[i]);
		i++;
	}
	free(info);
}

int		ft_rgb(int r, int g, int b)
{
	return (b | g << 8 | r << 16);
}

void	ft_free(char *s_res)
{
	if (s_res)
	{
		free(s_res);
		s_res = 0;
	}
}

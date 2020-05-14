/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:34:03 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 16:09:43 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_UTIL_H
# define LIBFT_UTIL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
size_t	ft_wordcount(char const *s1, char const c);
size_t	ft_checklen(char const *s1, char const c);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	free_info(char **info, char const *s, char c);
char	*ft_strjoin_point(char const *s1, char const *s2);
void	free_info(char **info, char const *s, char c);
int		RGB(int r, int g, int b);

#endif

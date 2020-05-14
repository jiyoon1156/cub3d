/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:12:27 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 18:31:21 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing_texture(t_pars *pars, int wc, char **info)
{
	if (ft_strncmp(info[0], "NO", ft_strlen(info[0])) == 0 && wc == 2)
		pars->no_path = ft_strdup(info[1]);
	else if (ft_strncmp(info[0], "SO", ft_strlen(info[0])) == 0 && wc == 2)
		pars->so_path = ft_strdup(info[1]);
	else if (ft_strncmp(info[0], "WE", ft_strlen(info[0])) == 0 && wc == 2)
		pars->we_path = ft_strdup(info[1]);
	else if (ft_strncmp(info[0], "EA", ft_strlen(info[0])) == 0 && wc == 2)
		pars->ea_path = ft_strdup(info[1]);
	else if (ft_strncmp(info[0], "S", ft_strlen(info[0])) == 0 && wc == 2)
		pars->sp_path = ft_strdup(info[1]);
	else
		return (ERROR);
	if (open(info[1], O_RDONLY) == -1)
		return (ERROR);
	return (1);
}

int	parsing_cf_color(t_pars *pars, int wc, char **info)
{
	char	**rgb;

	if (ft_strncmp(info[0], "C", ft_strlen(info[0])) == 0 && wc == 2)
	{
		if (ft_wordcount(info[1], ',') == 3)
			rgb = ft_split(info[1], ',');
		else
			return (ERROR);
		pars->c_color = ft_rgb(ft_atoi(rgb[0]),
		ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	else if (ft_strncmp(info[0], "F", ft_strlen(info[0])) == 0 && wc == 2)
	{
		if (ft_wordcount(info[1], ',') == 3)
			rgb = ft_split(info[1], ',');
		else
			return (ERROR);
		pars->f_color = ft_rgb(ft_atoi(rgb[0]),
		ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	}
	else
		return (ERROR);
	free_info(rgb, info[1], ',');
	return (1);
}

int	parsing_resolution(t_pars *pars, char **info)
{
	pars->resolution_w = ft_atoi(info[1]);
	pars->resolution_h = ft_atoi(info[2]);
	if (pars->resolution_w == 0 || pars->resolution_h == 0)
		return (ERROR);
	else if (pars->resolution_w * pars->resolution_h
	> WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		pars->resolution_w = WINDOW_WIDTH;
		pars->resolution_h = WINDOW_HEIGHT;
	}
	return (1);
}

int	parsing_info(t_pars *pars, char *line, char **info)
{
	int		wc;

	wc = ft_wordcount(line, ' ');
	if (ft_strncmp(info[0], "R", ft_strlen(info[0])) == 0 && wc == 3)
	{
		if (!parsing_resolution(pars, info))
			return (ERROR);
	}
	else if (ft_strchr("NSWE", info[0][0]))
	{
		if (!parsing_texture(pars, wc, info))
			return (ERROR);
	}
	else if (ft_strchr("CF", info[0][0]))
	{
		if (!parsing_cf_color(pars, wc, info))
			return (ERROR);
	}
	free_info(info, line, ' ');
	free(line);
	line = 0;
	return (1);
}

int	parsing(t_pars *pars, char *file, t_vars *vars)
{
	pars->line = 0;
	if ((pars->fd = open(file, O_RDONLY)) == -1)
		return (ERROR);
	while ((get_next_line(pars->fd, &(pars->line))) > 0)
	{
		if (*pars->line != '\0')
		{
			vars->info = ft_split(pars->line, ' ');
			if (ft_strchr("RNSWECF", vars->info[0][0]))
			{
				if (!parsing_info(pars, pars->line, vars->info))
					return (ERROR);
			}
			else
			{
				free_info(vars->info, pars->line, ' ');
				if (!read_map(pars->fd, pars->line, pars, vars))
					return (ERROR);
				break ;
			}
		}
		else
			free(pars->line);
	}
	return (1);
}

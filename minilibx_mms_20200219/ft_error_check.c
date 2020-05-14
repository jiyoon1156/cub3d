/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:06:30 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 17:33:37 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_error_updown(char **map, int w, int h)
{
	int y;

	y = 0;
	while (y < w)
	{
		if (!ft_strchr(" 1", map[0][y]) || !ft_strchr(" 1", map[h - 1][y]))
			return (ERROR);
		else if (map[0][y] == ' ' && !ft_strchr(" 1", map[1][y]))
			return (ERROR);
		else if (map[h - 1][y] == ' ' && !ft_strchr(" 1", map[h - 2][y]))
			return (ERROR);
		y++;
	}
	return (1);
}

static int	map_error_leftright(char **map, int w, int h)
{
	int x;

	x = 0;
	while (x < h)
	{
		if (!ft_strchr(" 1", map[x][0]) || !ft_strchr(" 1", map[x][w - 1]))
			return (ERROR);
		else if (map[x][0] == ' ' && !ft_strchr(" 1", map[x][1]))
			return (ERROR);
		else if (map[x][w - 1] == ' ' && !ft_strchr(" 1", map[x][w - 2]))
			return (ERROR);
		x++;
	}
	return (1);
}

static int	check_map(char **map, int x, int y, t_vars *vars)
{
	if (map[x][y] == ' ')
	{
		if (!ft_strchr(" 1", map[x - 1][y]) || !ft_strchr(" 1", map[x + 1][y])
			|| !ft_strchr(" 1", map[x][y - 1])
			|| !ft_strchr(" 1", map[x][y + 1]))
			return (ERROR);
	}
	else if (map[x][y] == '2')
	{
		vars->sp[vars->idx].sp_x = x;
		vars->sp[vars->idx].sp_y = y;
		vars->idx++;
	}
	return (1);
}

int			map_error(char **map, int w, int h, t_vars *vars)
{
	int x;
	int y;

	vars->idx = 0;
	if (!map_error_updown(map, w, h))
		return (ERROR);
	if (!map_error_leftright(map, w, h))
		return (ERROR);
	x = 1;
	while (x < h - 1)
	{
		y = 1;
		while (y < w - 1)
		{
			if (!check_map(map, x, y, vars))
				return (ERROR);
			y++;
		}
		x++;
	}
	return (1);
}

int			info_error(t_pars *pars)
{
	if (pars->no_path == NULL)
		return (ERROR);
	if (pars->we_path == NULL)
		return (ERROR);
	if (pars->so_path == NULL)
		return (ERROR);
	if (pars->ea_path == NULL)
		return (ERROR);
	if (pars->sp_path == NULL)
		return (ERROR);
	if (pars->resolution_h == 0 || pars->resolution_w == 0)
		return (ERROR);
	return (1);
}

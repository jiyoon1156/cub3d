/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:07:51 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 15:17:32 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_pos(t_vars *vars, int x, int y, char c)
{
	vars->posX = x + 0.5;
	vars->posY = y;
	if (c == 'N' || c == 'S')
	{
		vars->dirX = 0;
		vars->dirY = (c == 'N') ? 1 : -1;
		vars->planeX = 0.66;
		vars->planeY = 0;
	}
	else
	{
		vars->dirX = (c == 'E') ? 1 : -1;
		vars->dirY = 0;
		vars->planeX = 0;
		vars->planeY = 0.66;
	}
	return (1);
}

int	finding_map_element(t_vars *vars, char **map, int x, int y, t_pars *pars)
{
	if (ft_strchr(" 012NSEW", map[x][y]))
	{
		if (ft_strchr("NSEW", map[x][y]))
		{
			init_pos(vars, x, y, map[x][y]);
			vars->alpha_count++;
		}
		else if (map[x][y] == '2')
			vars->si.numSprites++;
		pars->map[x][y] = map[x][y];
	}
	else
		return (Error);
	return (1);
}

int	init_newmap(t_pars *pars, t_vars *vars, char **map)
{
	int x;
	int y;

	vars->alpha_count = 0;
	x = 0;
	vars->si.numSprites = 0;
	while (x < pars->height)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (!finding_map_element(vars, map, x, y, pars))
				return (Error);
			y++;
		}
		while (y < pars->width)
			pars->map[x][y++] = ' ';
		x++;
	}
	if (vars->alpha_count != 1)
		return (Error);
	return (1);
}

int	map_malloc(t_pars *pars, char **map)
{
	int len;
	int i;

	pars->width = 0;
	pars->height = 0;
	while (map[pars->height])
	{
		len = ft_strlen(map[pars->height]);
		if (pars->width < len)
			pars->width = len;
		pars->height++;
	}
	if (!(pars->map = malloc(sizeof(char *) * pars->height)))
		return (Error);
	i = 0;
	while (i < pars->height)
	{
		if (!(pars->map[i] = malloc(sizeof(char) * pars->width)))
			return (Error);
		i++;
	}
	return (1);
}

int	read_map(int fd, char *line, t_pars *pars, t_vars *vars)
{
	char *map_tmp;
	char **map;
	char *tmp;

	map_tmp = ft_strdup(line);
	free(line);
	line = 0;
	while ((get_next_line(fd, &line)) > 0)
	{
		tmp = map_tmp;
		map_tmp = ft_strjoin_point(map_tmp, line);
		free(tmp);
		free(line);
	}
	tmp = map_tmp;
	map_tmp = ft_strjoin_point(map_tmp, line);
	free(tmp);
	free(line);
	map = ft_split(map_tmp, '.');
	if (!map_malloc(pars, map))
		return (Error);
	if (!init_newmap(pars, vars, map))
		return (Error);
	vars->sp = malloc(sizeof(t_sp) * vars->si.numSprites);
	free_info(map, map_tmp, '.');
	free(map_tmp);
	if (!map_error(pars->map, pars->width, pars->height, vars))
		return (Error);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:07:51 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 18:28:58 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_pos(t_vars *vars, int x, int y, char c)
{
	vars->posx = x + 0.5;
	vars->posy = y;
	if (c == 'N' || c == 'S')
	{
		vars->dirx = 0;
		vars->diry = (c == 'N') ? 1 : -1;
		vars->planex = 0.66;
		vars->planey = 0;
	}
	else
	{
		vars->dirx = (c == 'E') ? 1 : -1;
		vars->diry = 0;
		vars->planex = 0;
		vars->planey = 0.66;
	}
	return (1);
}

int	finding_map_element(t_vars *vars, char **map, int x, int y)
{
	if (ft_strchr(" 012NSEW", map[x][y]))
	{
		if (ft_strchr("NSEW", map[x][y]))
		{
			init_pos(vars, x, y, map[x][y]);
			vars->alpha_count++;
		}
		else if (map[x][y] == '2')
			vars->si.numsprites++;
		vars->pars.map[x][y] = map[x][y];
	}
	else
		return (ERROR);
	return (1);
}

int	init_newmap(t_pars *pars, t_vars *vars, char **map)
{
	int x;
	int y;

	vars->alpha_count = 0;
	x = 0;
	vars->si.numsprites = 0;
	while (x < pars->height)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if (!finding_map_element(vars, map, x, y))
				return (ERROR);
			y++;
		}
		while (y < pars->width)
			pars->map[x][y++] = ' ';
		x++;
	}
	if (vars->alpha_count != 1)
		return (ERROR);
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
		return (ERROR);
	i = 0;
	while (i < pars->height)
	{
		if (!(pars->map[i] = malloc(sizeof(char) * pars->width)))
			return (ERROR);
		i++;
	}
	return (1);
}

int	read_map(int fd, char *line, t_pars *pars, t_vars *vars)
{
	t_gnl gnl;

	gnl.map_tmp = ft_strdup(line);
	ft_free(line);
	while ((get_next_line(fd, &line)) > 0)
	{
		gnl.tmp = gnl.map_tmp;
		gnl.map_tmp = ft_strjoin_point(gnl.map_tmp, line);
		ft_free(gnl.tmp);
		ft_free(line);
	}
	gnl.tmp = gnl.map_tmp;
	gnl.map_tmp = ft_strjoin_point(gnl.map_tmp, line);
	ft_free(gnl.tmp);
	ft_free(line);
	gnl.map = ft_split(gnl.map_tmp, '.');
	if (!map_malloc(pars, gnl.map) || !init_newmap(pars, vars, gnl.map))
		return (ERROR);
	vars->sp = malloc(sizeof(t_sp) * vars->si.numsprites);
	free_info(gnl.map, gnl.map_tmp, '.');
	ft_free(gnl.map_tmp);
	if (!map_error(pars->map, pars->width, pars->height, vars))
		return (ERROR);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:22:08 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 15:33:39 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_casting_info_1(t_vars *vars, int x, int w)
{
	vars->cameraX = 2 * x / (double)w - 1;
	vars->raydirX = vars->dirX + vars->planeX * vars->cameraX;
	vars->raydirY = vars->dirY + vars->planeY * vars->cameraX;
	vars->mapX = (int)(vars->posX);
	vars->mapY = (int)(vars->posY);
	vars->deltaDistX = fabs(1 / vars->raydirX);
	vars->deltaDistY = fabs(1 / vars->raydirY);
}

void	wall_casting_info_2(t_vars *vars)
{
	vars->hit = 0;
	if (vars->raydirX < 0)
	{
		vars->stepX = -1;
		vars->sideDistX = (vars->posX - vars->mapX) * vars->deltaDistX;
	}
	else
	{
		vars->stepX = 1;
		vars->sideDistX = (vars->mapX + 1.0 - vars->posX) * vars->deltaDistX;
	}
	if (vars->raydirY < 0)
	{
		vars->stepY = -1;
		vars->sideDistY = (vars->posY - vars->mapY) * vars->deltaDistY;
	}
	else
	{
		vars->stepY = 1;
		vars->sideDistY = (vars->mapY + 1.0 - vars->posY) * vars->deltaDistY;
	}
}

void	wall_casting_info_3(t_vars *vars)
{
	while (vars->hit == 0)
	{
		if (vars->sideDistX < vars->sideDistY)
		{
			vars->sideDistX += vars->deltaDistX;
			vars->mapX += vars->stepX;
			vars->side = 0;
		}
		else
		{
			vars->sideDistY += vars->deltaDistY;
			vars->mapY += vars->stepY;
			vars->side = 1;
		}
		if (vars->pars.map[vars->mapX][vars->mapY] == '1')
			vars->hit = 1;
	}
	if (vars->side == 0)
		vars->perpWallDist = (vars->mapX - vars->posX +
		(1 - vars->stepX) / 2) / vars->raydirX;
	else
		vars->perpWallDist = (vars->mapY - vars->posY +
		(1 - vars->stepY) / 2) / vars->raydirY;
}

void	wall_casting_info_4(t_vars *vars, int h)
{
	vars->lineHei = (int)(2 * h / vars->perpWallDist);
	vars->drawStart = vars->lineHei / -2 + h / 2;
	if (vars->drawStart < 0)
		vars->drawStart = 0;
	vars->drawEnd = vars->lineHei / 2 + h / 2;
	if (vars->drawEnd >= h)
		vars->drawEnd = h - 1;
	if (vars->side == 0)
		vars->wallX = vars->posY + vars->perpWallDist * vars->raydirY;
	else
		vars->wallX = vars->posX + vars->perpWallDist * vars->raydirX;
	vars->wallX -= floor((vars->wallX));
	vars->texX = (int)(vars->wallX * (double)(texWidth));
	if (vars->side == 0 && vars->raydirX > 0)
		vars->texX = texWidth - vars->texX - 1;
	if (vars->side == 1 && vars->raydirY < 0)
		vars->texX = texWidth - vars->texX - 1;
	vars->step = 1.0 * texHeight / vars->lineHei;
	vars->texPos = (vars->drawStart - h / 2 + vars->lineHei / 2) * vars->step;
}

void	render(t_vars *vars)
{
	int		x;
	int		i;
	int		w;
	int		h;
	double	Zbuffer[vars->pars.resolution_w];

	w = vars->pars.resolution_w;
	h = vars->pars.resolution_h;
	x = 0;
	while (x < w)
	{
		wall_casting_info_1(vars, x, w);
		wall_casting_info_2(vars);
		wall_casting_info_3(vars);
		wall_casting_info_4(vars, h);
		dotting(vars, x, vars->drawStart, vars->drawEnd, vars->side);
		Zbuffer[x] = vars->perpWallDist;
		++x;
	}
	sp_casting(vars, Zbuffer);
}

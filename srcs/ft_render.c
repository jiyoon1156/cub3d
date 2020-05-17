/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:22:08 by jhur              #+#    #+#             */
/*   Updated: 2020/05/17 13:57:39 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_casting_info_1(t_vars *vars, int x, int w)
{
	vars->camerax = 2 * x / (double)w - 1;
	vars->raydirx = vars->dirx + vars->planex * vars->camerax;
	vars->raydiry = vars->diry + vars->planey * vars->camerax;
	vars->mapx = (int)(vars->posx);
	vars->mapy = (int)(vars->posy);
	vars->deltadistx = fabs(1 / vars->raydirx);
	vars->deltadisty = fabs(1 / vars->raydiry);
}

void	wall_casting_info_2(t_vars *vars)
{
	vars->hit = 0;
	if (vars->raydirx < 0)
	{
		vars->stepx = -1;
		vars->sidedistx = (vars->posx - vars->mapx) * vars->deltadistx;
	}
	else
	{
		vars->stepx = 1;
		vars->sidedistx = (vars->mapx + 1.0 - vars->posx) * vars->deltadistx;
	}
	if (vars->raydiry < 0)
	{
		vars->stepy = -1;
		vars->sidedisty = (vars->posy - vars->mapy) * vars->deltadisty;
	}
	else
	{
		vars->stepy = 1;
		vars->sidedisty = (vars->mapy + 1.0 - vars->posy) * vars->deltadisty;
	}
}

void	wall_casting_info_3(t_vars *vars)
{
	while (vars->hit == 0)
	{
		if (vars->sidedistx < vars->sidedisty)
		{
			vars->sidedistx += vars->deltadistx;
			vars->mapx += vars->stepx;
			vars->side = 0;
		}
		else
		{
			vars->sidedisty += vars->deltadisty;
			vars->mapy += vars->stepy;
			vars->side = 1;
		}
		if (vars->pars.map[vars->mapx][vars->mapy] == '1')
			vars->hit = 1;
	}
	if (vars->side == 0)
		vars->perpwalldist = (vars->mapx - vars->posx +
		(1 - vars->stepx) / 2) / vars->raydirx;
	else
		vars->perpwalldist = (vars->mapy - vars->posy +
		(1 - vars->stepy) / 2) / vars->raydiry;
}

void	wall_casting_info_4(t_vars *vars, int h)
{
	vars->linehei = (int)(2 * h / vars->perpwalldist);
	vars->drawstart = vars->linehei / -2 + h / 2;
	if (vars->drawstart < 0)
		vars->drawstart = 0;
	vars->drawend = vars->linehei / 2 + h / 2;
	if (vars->drawend >= h)
		vars->drawend = h - 1;
	if (vars->side == 0)
		vars->wallx = vars->posy + vars->perpwalldist * vars->raydiry;
	else
		vars->wallx = vars->posx + vars->perpwalldist * vars->raydirx;
	vars->wallx -= floor((vars->wallx));
	vars->texx = (int)(vars->wallx * (double)(TEX_WIDTH));
	if (vars->side == 0 && vars->raydirx > 0)
		vars->texx = TEX_WIDTH - vars->texx - 1;
	if (vars->side == 1 && vars->raydiry < 0)
		vars->texx = TEX_WIDTH - vars->texx - 1;
	vars->step = 1.0 * TEX_HEIGHT / vars->linehei;
	vars->texpos = (vars->drawstart - h / 2 + vars->linehei / 2) * vars->step;
}

void	render(t_vars *vars)
{
	int		x;
	int		w;
	int		h;
	double	zbuffer[vars->pars.resolution_w];

	w = vars->pars.resolution_w;
	h = vars->pars.resolution_h;
	x = 0;
	while (x < w)
	{
		wall_casting_info_1(vars, x, w);
		wall_casting_info_2(vars);
		wall_casting_info_3(vars);
		wall_casting_info_4(vars, h);
		dotting(vars, x, vars->side);
		zbuffer[x] = vars->perpwalldist;
		++x;
	}
	sp_casting(vars, zbuffer);
}

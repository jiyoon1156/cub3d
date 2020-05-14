/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:17:41 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 15:03:37 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verLine(t_vars vars, int x, int drawStart, int drawEnd, int color)
{
	int	y;

	y = drawStart;
	while (y < drawEnd)
	{
		vars.img.data[y * vars.pars.resolution_w + x] = color;
		++y;
	}
}

int		get_color(t_vars *vars, int side)
{
	vars->texY = (int)(vars->texPos) & (texHeight - 1);
	vars->texPos += vars->step;
	if (side == 1 && vars->raydirY >= 0)
		return (vars->tex[0].data)[vars->texWid * vars->texY + vars->texX];
	else if (side == 1 && vars->raydirY < 0)
		return (vars->tex[1].data)[vars->texWid * vars->texY + vars->texX];
	else if (side == 0 && vars->raydirX >= 0)
		return (vars->tex[2].data)[vars->texWid * vars->texY + vars->texX];
	else
		return (vars->tex[3].data)[vars->texWid * vars->texY + vars->texX];
}

void	dotting(t_vars *vars, int x, int drawStart, int drawEnd, int side)
{
	int	y;
	int	ceil;
	int	color;

	y = drawStart;
	ceil = 0;
	while (ceil < y)
	{
		color = vars->pars.c_color;
		vars->img.data[ceil * vars->pars.resolution_w + x] = color;
		++ceil;
	}
	while (y < drawEnd)
	{
		color = get_color(vars, side);
		vars->img.data[y * vars->pars.resolution_w + x] = color;
		++y;
	}
	while (y < vars->pars.resolution_h)
	{
		color = vars->pars.f_color;
		vars->img.data[y * vars->pars.resolution_w + x] = color;
		++y;
	}
}

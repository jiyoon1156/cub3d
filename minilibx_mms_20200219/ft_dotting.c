/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dotting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:17:41 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 18:05:40 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_color(t_vars *vars, int side)
{
	vars->texy = (int)(vars->texpos) & (TEX_HEIGHT - 1);
	vars->texpos += vars->step;
	if (side == 1 && vars->raydiry >= 0)
		return (vars->tex[0].data)[vars->texwid * vars->texy + vars->texx];
	else if (side == 1 && vars->raydiry < 0)
		return (vars->tex[1].data)[vars->texwid * vars->texy + vars->texx];
	else if (side == 0 && vars->raydirx >= 0)
		return (vars->tex[2].data)[vars->texwid * vars->texy + vars->texx];
	else
		return (vars->tex[3].data)[vars->texwid * vars->texy + vars->texx];
}

void	dotting(t_vars *vars, int x, int side)
{
	int	y;
	int	ceil;
	int	color;

	y = vars->drawstart;
	ceil = 0;
	while (ceil < y)
	{
		color = vars->pars.c_color;
		vars->img.data[ceil * vars->pars.resolution_w + x] = color;
		++ceil;
	}
	while (y < vars->drawend)
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

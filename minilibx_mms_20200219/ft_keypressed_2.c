/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypressed_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:19:29 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 15:12:48 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_forward(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posX + vars->dirX)][(int)(vars->posY)]
	!= '1')
		vars->posX += vars->dirX * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posX)][(int)(vars->posY + vars->dirY)]
	!= '1')
		vars->posY += (vars->dirY) * vars->moving_speed;
}

void	go_backward(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posX - vars->dirX)][(int)(vars->posY)]
	!= '1')
		vars->posX -= vars->dirX * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posX)][(int)(vars->posY - vars->dirY)]
	!= '1')
		vars->posY -= vars->dirY * vars->moving_speed;
}

void	go_right(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posX + vars->planeX)][(int)(vars->posY)]
	!= '1')
		vars->posX += (vars->planeX) * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posX)][(int)(vars->posY + vars->planeY)]
	!= '1')
		vars->posY += (vars->planeY) * vars->moving_speed;
}

void	go_left(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posX - vars->planeX)][(int)(vars->posY)]
	!= '1')
		vars->posX -= (vars->planeX) * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posX)][(int)(vars->posY - vars->planeY)]
	!= '1')
		vars->posY -= (vars->planeY) * vars->moving_speed;
}

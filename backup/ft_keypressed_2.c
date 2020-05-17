/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypressed_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:19:29 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 17:19:21 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	go_forward(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posx + vars->dirx)][(int)(vars->posy)]
	!= '1')
		vars->posx += vars->dirx * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posx)][(int)(vars->posy + vars->diry)]
	!= '1')
		vars->posy += (vars->diry) * vars->moving_speed;
}

void	go_backward(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posx - vars->dirx)][(int)(vars->posy)]
	!= '1')
		vars->posx -= vars->dirx * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posx)][(int)(vars->posy - vars->diry)]
	!= '1')
		vars->posy -= vars->diry * vars->moving_speed;
}

void	go_right(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posx + vars->planex)][(int)(vars->posy)]
	!= '1')
		vars->posx += (vars->planex) * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posx)][(int)(vars->posy + vars->planey)]
	!= '1')
		vars->posy += (vars->planey) * vars->moving_speed;
}

void	go_left(t_vars *vars)
{
	if (vars->pars.map[(int)(vars->posx - vars->planex)][(int)(vars->posy)]
	!= '1')
		vars->posx -= (vars->planex) * vars->moving_speed;
	if (vars->pars.map[(int)(vars->posx)][(int)(vars->posy - vars->planey)]
	!= '1')
		vars->posy -= (vars->planey) * vars->moving_speed;
}

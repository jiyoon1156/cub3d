/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypressed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:20:30 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 17:44:43 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_vars *vars)
{
	vars->olddirx = vars->dirx;
	vars->dirx = vars->dirx * cos(-vars->rot_speed) -
	vars->diry * sin(-vars->rot_speed);
	vars->diry = vars->olddirx * sin(-vars->rot_speed) +
	vars->diry * cos(-vars->rot_speed);
	vars->oldplanex = vars->planex;
	vars->planex = vars->planex * cos(-vars->rot_speed) -
	vars->planey * sin(-vars->rot_speed);
	vars->planey = vars->oldplanex * sin(-vars->rot_speed) +
	vars->planey * cos(-vars->rot_speed);
}

void	rotate_left(t_vars *vars)
{
	vars->olddirx = vars->dirx;
	vars->dirx = vars->dirx * cos(vars->rot_speed) -
	vars->diry * sin(vars->rot_speed);
	vars->diry = vars->olddirx * sin(vars->rot_speed) +
	vars->diry * cos(vars->rot_speed);
	vars->oldplanex = vars->planex;
	vars->planex = vars->planex * cos(vars->rot_speed) -
	vars->planey * sin(vars->rot_speed);
	vars->planey = vars->oldplanex * sin(vars->rot_speed) +
	vars->planey * cos(vars->rot_speed);
}

int		key_pressed(int keycode, t_vars *vars)
{
	vars->moving_speed = 0.1;
	vars->rot_speed = 0.2;
	if (keycode == K_W)
		go_forward(vars);
	if (keycode == K_S)
		go_backward(vars);
	if (keycode == K_D)
		go_right(vars);
	if (keycode == K_A)
		go_left(vars);
	if (keycode == K_AR_R)
		rotate_right(vars);
	if (keycode == K_AR_L)
		rotate_left(vars);
	if (keycode == K_ESC)
		exit(0);
	mlx_clear_window(vars->mlx, vars->win);
	render(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	return (0);
}

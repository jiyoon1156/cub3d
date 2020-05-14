/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypressed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:20:30 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 15:16:07 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_right(t_vars *vars)
{
	vars->olddirX = vars->dirX;
	vars->dirX = vars->dirX * cos(-vars->rot_speed) -
	vars->dirY * sin(-vars->rot_speed);
	vars->dirY = vars->olddirX * sin(-vars->rot_speed) +
	vars->dirY * cos(-vars->rot_speed);
	vars->oldplaneX = vars->planeX;
	vars->planeX = vars->planeX * cos(-vars->rot_speed) -
	vars->planeY * sin(-vars->rot_speed);
	vars->planeY = vars->oldplaneX * sin(-vars->rot_speed) +
	vars->planeY * cos(-vars->rot_speed);
}

void	rotate_left(t_vars *vars)
{
	vars->olddirX = vars->dirX;
	vars->dirX = vars->dirX * cos(vars->rot_speed) -
	vars->dirY * sin(vars->rot_speed);
	vars->dirY = vars->olddirX * sin(vars->rot_speed) +
	vars->dirY * cos(vars->rot_speed);
	vars->oldplaneX = vars->planeX;
	vars->planeX = vars->planeX * cos(vars->rot_speed) -
	vars->planeY * sin(vars->rot_speed);
	vars->planeY = vars->oldplaneX * sin(vars->rot_speed) +
	vars->planeY * cos(vars->rot_speed);
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
	if (keycode == K_AR_L)
		rotate_right(vars);
	if (keycode == K_AR_R)
		rotate_left(vars);
	if (keycode == K_ESC)
		exit(0);
	mlx_clear_window(vars->mlx, vars->win);
	render(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
	return (0);
}

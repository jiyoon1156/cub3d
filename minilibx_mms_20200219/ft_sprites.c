/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:25:30 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 16:01:56 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sortSprites(t_sp *sprite, int n)
{
	int		i;
	int		j;
	t_sp	temp;

	i = n - 1;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (sprite[j].sp_dist < sprite[j + 1].sp_dist)
			{
				temp = sprite[j];
				sprite[j] = sprite[j + 1];
				sprite[j + 1] = temp;
			}
			j++;
		}
		i--;
	}
}

void	init_sp_info(t_vars *vars, int w, int h, t_sp *sprite, int i)
{
	double	spriteX;
	double	spriteY;
	double	invDet;

	spriteX = sprite[i].sp_x - vars->posX;
	spriteY = sprite[i].sp_y - vars->posY;
	invDet = 1.0 / (vars->planeX * vars->dirY - vars->dirX * vars->planeY);
	vars->si.tX = invDet * (vars->dirY * spriteX - vars->dirX * spriteY);
	vars->si.tY = invDet * (-vars->planeY * spriteX + vars->planeX * spriteY);
	vars->si.spriteScreenX = (int)((w / 2) * (1 + vars->si.tX / vars->si.tY));
	vars->si.vMS = (int)(vMove / vars->si.tY);
	vars->si.sp_Hei = abs((int)(h / (vars->si.tY))) / vDiv;
	vars->si.drawStartY = -vars->si.sp_Hei / 2 + h / 2 + vars->si.vMS;
	if (vars->si.drawStartY < 0)
		vars->si.drawStartY = 0;
	vars->si.drawEndY = vars->si.sp_Hei / 2 + h / 2 + vars->si.vMS;
	if (vars->si.drawEndY >= h)
		vars->si.drawEndY = h - 1;
	vars->si.spriteWidth = abs((int)(h / (vars->si.tY))) / uDiv;
	vars->si.drawStartX = -vars->si.spriteWidth / 2 + vars->si.spriteScreenX;
	if (vars->si.drawStartX < 0)
		vars->si.drawStartX = 0;
	vars->si.drawEndX = vars->si.spriteWidth / 2 + vars->si.spriteScreenX;
	if (vars->si.drawEndX >= w)
		vars->si.drawEndX = w - 1;
}

void	sp_drawing(t_vars *vars, int w, int h, double *Zbuffer)
{
	int		y;
	int		d;
	int		c;
	int		sti;

	sti = vars->si.drawStartX;
	while (sti < vars->si.drawEndX)
	{
		vars->si.stX = (int)(256 * (sti - (-vars->si.spriteWidth
		/ 2 + vars->si.spriteScreenX)) * texWidth / vars->si.spriteWidth) / 256;
		if (vars->si.tY > 0 && sti > 0 && sti < w && vars->si.tY < Zbuffer[sti])
		{
			y = vars->si.drawStartY;
			while (y < vars->si.drawEndY)
			{
				d = (y - vars->si.vMS) * 256 - h * 128 + vars->si.sp_Hei * 128;
				vars->si.stY = ((d * texHeight) / vars->si.sp_Hei) / 256;
				c = (vars->tex[4].data)[vars->texWid * vars->si.stY
				+ vars->si.stX];
				if (c != 0x000000)
					vars->img.data[y * vars->pars.resolution_w + sti] = c;
				y++;
			}
		}
		sti++;
	}
}

void	sp_casting(t_vars *vars, double *Zbuffer)
{
	int		w;
	int		h;
	int		i;

	w = vars->pars.resolution_w;
	h = vars->pars.resolution_h;
	i = 0;
	while (i < vars->si.numSprites)
	{
		vars->sp[i].sp_dist = ((vars->posX - vars->sp[i].sp_x) *
		(vars->posX - vars->sp[i].sp_x) + (vars->posY - vars->sp[i].sp_y) *
		(vars->posY - vars->sp[i].sp_y));
		i++;
	}
	sortSprites(vars->sp, vars->si.numSprites);
	i = 0;
	while (i < vars->si.numSprites)
	{
		init_sp_info(vars, w, h, vars->sp, i);
		sp_drawing(vars, w, h, Zbuffer);
		i++;
	}
}

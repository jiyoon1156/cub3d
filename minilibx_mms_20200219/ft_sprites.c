/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:25:30 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 18:03:38 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sortsprites(t_sp *sprite, int n)
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

void	init_sp_info(t_vars *vars, int w, int h, int i)
{
	double	spritex;
	double	spritey;
	double	invdet;

	spritex = vars->sp[i].sp_x - vars->posx;
	spritey = vars->sp[i].sp_y - vars->posy;
	invdet = 1.0 / (vars->planex * vars->diry - vars->dirx * vars->planey);
	vars->si.tx = invdet * (vars->diry * spritex - vars->dirx * spritey);
	vars->si.ty = invdet * (-vars->planey * spritex + vars->planex * spritey);
	vars->si.spritescreenx = (int)((w / 2) * (1 + vars->si.tx / vars->si.ty));
	vars->si.vms = (int)(VMOVE / vars->si.ty);
	vars->si.sp_hei = abs((int)(h / (vars->si.ty))) / VDIV;
	vars->si.drawstarty = -vars->si.sp_hei / 2 + h / 2 + vars->si.vms;
	if (vars->si.drawstarty < 0)
		vars->si.drawstarty = 0;
	vars->si.drawendy = vars->si.sp_hei / 2 + h / 2 + vars->si.vms;
	if (vars->si.drawendy >= h)
		vars->si.drawendy = h - 1;
	vars->si.spritewidth = abs((int)(h / (vars->si.ty))) / UDIV;
	vars->si.drawstartx = -vars->si.spritewidth / 2 + vars->si.spritescreenx;
	if (vars->si.drawstartx < 0)
		vars->si.drawstartx = 0;
	vars->si.drawendx = vars->si.spritewidth / 2 + vars->si.spritescreenx;
	if (vars->si.drawendx >= w)
		vars->si.drawendx = w - 1;
}

void	sp_drawing(t_vars *vars, int w, int h, double *zbuffer)
{
	int		y;
	int		c;
	int		sti;

	sti = vars->si.drawstartx;
	while (sti < vars->si.drawendx)
	{
		vars->si.stx = (int)(256 * (sti - (-vars->si.spritewidth / 2
		+ vars->si.spritescreenx)) * TEX_WIDTH / vars->si.spritewidth) / 256;
		if (vars->si.ty > 0 && sti > 0 && sti < w && vars->si.ty < zbuffer[sti])
		{
			y = vars->si.drawstarty;
			while (y < vars->si.drawendy)
			{
				vars->si.sty = ((((y - vars->si.vms) * 256 - h * 128 +
				vars->si.sp_hei * 128) * TEX_HEIGHT) / vars->si.sp_hei) / 256;
				c = (vars->tex[4].data)[vars->texwid * vars->si.sty
				+ vars->si.stx];
				if (c != 0x000000)
					vars->img.data[y * vars->pars.resolution_w + sti] = c;
				y++;
			}
		}
		sti++;
	}
}

void	sp_casting(t_vars *vars, double *zbuffer)
{
	int		w;
	int		h;
	int		i;

	w = vars->pars.resolution_w;
	h = vars->pars.resolution_h;
	i = 0;
	while (i < vars->si.numsprites)
	{
		vars->sp[i].sp_dist = ((vars->posx - vars->sp[i].sp_x) *
		(vars->posx - vars->sp[i].sp_x) + (vars->posy - vars->sp[i].sp_y) *
		(vars->posy - vars->sp[i].sp_y));
		i++;
	}
	sortsprites(vars->sp, vars->si.numsprites);
	i = 0;
	while (i < vars->si.numsprites)
	{
		init_sp_info(vars, w, h, i);
		sp_drawing(vars, w, h, zbuffer);
		i++;
	}
}

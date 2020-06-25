/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:23:18 by jhur              #+#    #+#             */
/*   Updated: 2020/06/25 13:28:08 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_struct_save(t_vars *vars, t_save *s)
{
	s->size = 54 + 4 * vars->pars.resolution_w * vars->pars.resolution_h;
	s->unused = 0;
	s->offset_begin = 54;
	s->header_bytes = 40;
	s->plane = 1;
	s->bpixel = 32;
	s->fd = open("cub3d.bmp", O_RDWR | O_CREAT, S_IRWXU | O_TRUNC);
	if (s->fd == -1)
		write(1, "Error\n", 6);
}

void	ft_write_texture_bmp_file(t_vars *vars, int fd)
{
	int		y;
	int		x;
	int		line;

	y = 0;
	while (y < vars->pars.resolution_h)
	{
		x = 0;
		line = vars->pars.resolution_w * (vars->pars.resolution_h - y);
		while (x < vars->pars.resolution_w)
		{
			write(fd, &vars->img.data[line], 4);
			line++;
			x++;
		}
		y++;
	}
}

int		ft_write_bmp_file(t_vars *vars)
{
	t_save	s;

	ft_init_struct_save(vars, &s);
	write(s.fd, "BM", 2);
	write(s.fd, &s.size, sizeof(int));
	write(s.fd, &s.unused, sizeof(int));
	write(s.fd, &s.offset_begin, sizeof(int));
	write(s.fd, &s.header_bytes, sizeof(int));
	write(s.fd, &vars->pars.resolution_w, sizeof(int));
	write(s.fd, &vars->pars.resolution_h, sizeof(int));
	write(s.fd, &s.plane, sizeof(short int));
	write(s.fd, &s.bpixel, sizeof(short int));
	write(s.fd, &s.unused, sizeof(int));
	write(s.fd, &s.unused, sizeof(int));
	write(s.fd, &s.unused, sizeof(int));
	write(s.fd, &s.unused, sizeof(int));
	write(s.fd, &s.unused, sizeof(int));
	write(s.fd, &s.unused, sizeof(int));
	ft_write_texture_bmp_file(vars, s.fd);
	close(s.fd);
	return (0);
}

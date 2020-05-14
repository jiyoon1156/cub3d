/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:34:17 by jhur              #+#    #+#             */
/*   Updated: 2020/05/14 15:45:42 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# include "mlx.h"
# include "keycode.h"
# include "get_next_line.h"
# include "libft_util.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define window_width 800
# define window_height 800
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24
# define uDiv 0.5
# define vDiv 0.5
# define vMove 100
# define Error 0

typedef struct	s_save
{
    int	size;
    int	unused;
    int	offset_begin;
    int	header_bytes;
    int	plane;
    int	bpixel;
    int	fd;
}				t_save;

typedef struct	s_data
{
	void	*img_ptr;
	int		*data;
	int		size_line;
	int		bpp;
	int		endian;
}				t_data;
typedef struct	s_pars
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sp_path;
	int		resolution_w;
	int		resolution_h;
	int		c_color;
	int		f_color;
	char	**map;
	int		height;
	int		width;
	int		fd;
	char	*line;
}				t_pars;
typedef struct	s_sp_info
{
	double	tX;
	double	tY;
	int		spriteScreenX;
	int		vMS;
	int		sp_Hei;
	int		drawStartY;
	int		drawEndY;
	int		spriteWidth;
	int		drawStartX;
	int		drawEndX;
	int		stX;
	int		stY;
	int		numSprites;
}				t_sp_info;
typedef struct	s_sp
{
	double	sp_x;
	double	sp_y;
	double	sp_dist;
}				t_sp;
typedef struct	s_vars {
	void		*mlx;
	void		*win;
	int			color;
	char		*string;
	double		posX;
	double		posY;
	double		raydirX;
	double		olddirX;
	double		dirX;
	double		raydirY;
	double		olddirY;
	double		dirY;
	double		rot_speed;
	double		moving_speed;
	double		oldplaneX;
	double		planeX;
	double		planeY;
	int			mapX;
	int			mapY;
	t_data		img;
	int			key;
	double		texPos;
	double		step;
	int			texX;
	int			texY;
	int			texNum;
	t_data		tex[5];
	int			texWid;
	int			texHei;
	t_pars		pars;
	t_sp_info	si;
	t_sp		*sp;
	int			idx;
	double		cameraX;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHei;
	int			drawStart;
	int			drawEnd;
	double		wallX;
	int			alpha_count;
}				t_vars;

void			dotting(t_vars *vars, int x, int drawStart,
int drawEnd, int side);
int				key_pressed(int keycode, t_vars *vars);
void			render(t_vars *vars);
int				parsing(t_pars *pars, char *file, t_vars *vars);
int				read_map(int fd, char *line, t_pars *pars, t_vars *vars);
void			sp_casting(t_vars *vars, double *Zbuffer);
int				init_pos(t_vars *vars, int x, int y, char c);
int				map_error(char **map, int w, int h, t_vars *vars);
char			*ft_strchr(const char *s, int c);
int				info_error(t_pars *pars);
void			ft_write_bmp_file(t_vars *vars);
void			go_forward(t_vars *vars);
void			go_backward(t_vars *vars);
void			go_right(t_vars *vars);
void			go_left(t_vars *vars);
void			render(t_vars *vars);

#endif

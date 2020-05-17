/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhur <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 14:34:17 by jhur              #+#    #+#             */
/*   Updated: 2020/05/17 14:07:11 by jhur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H
# define _CUB3D_H

# include "../minilibx/mlx.h"
# include "keycode.h"
# include "get_next_line.h"
# include "libft_util.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define UDIV 0.5
# define VDIV 0.5
# define VMOVE 100
# define ERROR 0

typedef struct	s_gnl
{
	char	*map_tmp;
	char	**map;
	char	*tmp;
}				t_gnl;
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
	double	tx;
	double	ty;
	int		spritescreenx;
	int		vms;
	int		sp_hei;
	int		drawstarty;
	int		drawendy;
	int		spritewidth;
	int		drawstartx;
	int		drawendx;
	int		stx;
	int		sty;
	int		numsprites;
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
	double		posx;
	double		posy;
	double		raydirx;
	double		olddirx;
	double		dirx;
	double		raydiry;
	double		olddiry;
	double		diry;
	double		rot_speed;
	double		moving_speed;
	double		oldplanex;
	double		planex;
	double		planey;
	int			mapx;
	int			mapy;
	t_data		img;
	int			key;
	double		texpos;
	double		step;
	int			texx;
	int			texy;
	t_data		tex[5];
	int			texwid;
	int			texhei;
	t_pars		pars;
	t_sp_info	si;
	t_sp		*sp;
	int			idx;
	double		camerax;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			linehei;
	int			drawstart;
	int			drawend;
	double		wallx;
	int			alpha_count;
	char		**info;
}				t_vars;

void			dotting(t_vars *vars, int x, int side);
int				key_pressed(int keycode, t_vars *vars);
void			render(t_vars *vars);
int				parsing(t_pars *pars, char *file, t_vars *vars);
int				read_map(int fd, char *line, t_pars *pars, t_vars *vars);
void			sp_casting(t_vars *vars, double *zbuffer);
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

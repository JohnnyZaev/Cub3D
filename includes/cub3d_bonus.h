/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:23:25 by gvarys            #+#    #+#             */
/*   Updated: 2022/04/29 15:38:28 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <time.h>
# include "../minilibx_opengl/mlx.h"
# include "../libft/libft.h"

# define TAIL_SIZE	64
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define RC_ROTATE 123
# define CL_ROTATE 124
# define ESC 53

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		speed;
}	t_player;

typedef struct s_keys
{
	bool		forward;
	bool		back;
	bool		right;
	bool		left;
	bool		rightr;
	bool		leftr;
	bool		exit;
}					t_keys;

typedef struct s_img
{
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
}					t_img;

typedef struct s_draws
{
	int		tocheck;
	double	rayang;
	double	xsps;
	double	ysps;
	double	xint;
	double	yint;
	double	nhorx;
	double	nhory;
	double	hwhitx;
	double	hwhity;
	int		fhwhit;
	int		vwallhit;
	double	hdistnc;
	double	vdistnc;
	double	vwhitx;
	double	vwhity;
}					t_draws;

typedef struct s_rays
{
	double	wallhx;
	double	wallhy;
	int		down;
	int		up;
	int		right;
	int		left;
	int		hitvert;
	double	distance;
	double	angle;
}					t_rays;

typedef struct s_render {
	double	raydist;
	double	distpj;
	double	wallstrip;
	double	top;
	double	distancetop;
	double	bottom;
	int		i;
	double	j;
}				t_render;

typedef struct s_mlx_god
{
	void		*mlx;
	void		*win;
	t_player	*player;
	char		**map;
	int			size_x;
	int			size_y;
	int			map_size_x;
	int			map_size_y;
	int			f_color;
	int			c_color;
	char		*textures[4];
	int			*texturep[4];
	t_keys		*keys;
	t_draws		*draws;
	t_img		img;
	t_rays		*rays;
	t_render	*render;
	int			txtx;
	int			txty;
}				t_mlx_god;

//drawrays.c
void		drawrays(t_mlx_god *god);
void		ft_halfone(int i, t_mlx_god *god);
void		ft_halftwo(int i, t_mlx_god *god);

// parser.c
int			parser(t_mlx_god *god, char *file_name);

// parser/check_map
int			check_map(t_mlx_god *god);

// parser/parser_element_part.c
int			parse_textures_and_color(t_mlx_god *god, char *file_name, int *fd);

// parser/parse_color.c
int			get_color(t_mlx_god *god, char *flags, int i, char *str);
int			write_to_textures_massive(t_mlx_god *god, char *flags, \
				int i, char *str);

//utils
int			errors(int err);
int			esc(t_mlx_god *god);

// utils/initialization.c
void		ft_init(t_mlx_god *god, t_player *player);
void		set_textures(t_mlx_god *god);

// game_loop.c
int			game_loop(t_mlx_god *god);
int			press(int key, t_keys *keys);
int			unhold(int key, t_keys *keys);

// ft_clean.c
void		ft_clean(t_mlx_god *god, int mode);

//render.c
void		render3d(t_mlx_god *god);

//utils.c
int			is_wall(double y, double x, t_mlx_god *god);
double		ft_norm(double ray_ang);
double		distance_bew_points(double x, double y, double xd, double yd);

#endif
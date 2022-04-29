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

#ifndef CUB3D_H
# define CUB3D_H

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
# define NOSE_SIZE	64
# define PI			3.14159265359
# define CONV		(PI/180)
# define INV       (180/PI)
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define RC_ROTATE 12
# define CL_ROTATE 14
# define RESET 15
# define ESC 53

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	int		v_range;
	int		speed;
}	t_player;

typedef struct		s_keys
{
	bool		forward;
	bool		back;
	bool		right;
	bool		left;
	bool		rightr;
	bool		leftr;
	bool		up;
	bool		down;
	bool		exit;
}					t_keys;

typedef struct		s_img
{
	void		*img_ptr;
	int			*data;
	int			bpp;
	int			size_line;
	int			endian;
}					t_img;

typedef struct		s_draws
{
	int		tocheck;
	float	rayang;
	float	xsps;
	float	ysps;
	float	xint;
	float	yint;
	float	nhorx;
	float	nhory;
	float	hwhitx;
	float	hwhity;
	int		fhwhit;
	int		vwallhit;
	float	hdistnc;
	float	vdistnc;
	float	vwhitx;
	float	vwhity;
}					t_draws;

typedef struct		s_rays
{
	float	wallhx;
	float	wallhy;
	int		down;
	int		up;
	int		right;
	int		left;
	int		hitvert;
	float	distance;
	float	angle;
}					t_rays;

typedef struct		s_render {
	float raydist;
	float distpj;
	float wallstrip;
	float top;
	float distancetop;
	float bottom;
	int i;
	float j;
}					t_render;

typedef struct s_mlx_god
{
	double 		x;
	double 		y;
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
	int 		*texturep[4];
	t_keys 		*keys;
	t_draws 	*draws;
	t_img		img;
	t_rays 		*rays;
	t_render	*render;
	int			txtx;
	int			txty;
} t_mlx_god;

int			errors(int err);
int			ecs(t_mlx_god *god);
int			press(int key, t_keys *keys);
int			unpress(int key, t_keys *keys);
double		distance_bew_points(float x, float y, float xd, float yd);
void		drawrays(t_mlx_god *god);
int			ft_iswal(float y, float x, t_mlx_god *god);
float		ft_norm(float rayang);

// drawing.c
void	print_player_dot(t_player*	player, t_mlx_god*	god);
void	print_rectangle(t_mlx_god*	god, int id_x, int id_y, int width, int heith, int colour);
void	draw_map(t_mlx_god*	god);
void	print_line(t_mlx_god*	god, int id_x, int id_y, int end_x, int end_y);
void	print_player_ray(t_mlx_god*	god, t_player* player);

// parser.c
void	parser(t_mlx_god* god, char *file_name);
// parser_element_part.c
int		parse_textures_and_color(t_mlx_god* god, char *file_name, int *fd);

// ft_clean.c
void	ft_clean(t_mlx_god*	god, int mode);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:23:25 by gvarys            #+#    #+#             */
/*   Updated: 2022/04/12 12:44:27 by ereginia         ###   ########.fr       */
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

typedef struct s_mlx_god
{
	void		*mlx;
	void		*win;
	t_player	*player;
	char		**map;
	int			size_x;
	int			size_y;
	int			f_color;
	int			c_color;
	char		*textures[4];
} t_mlx_god;

int	errors(int err);

// drawing.c
void	print_player_dot(t_player*	player, t_mlx_god*	god);
void	print_rectangle(t_mlx_god*	god, int id_x, int id_y, int width, int heith);
void	print_line(t_mlx_god*	god, int id_x, int id_y, int end_x, int end_y);
void	print_player_ray(t_mlx_god*	god, t_player* player);

// parser.c
void	parser(t_mlx_god* god, char *file_name);

#endif
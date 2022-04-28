/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 12:17:16 by ereginia          #+#    #+#             */
/*   Updated: 2022/04/12 12:23:11 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player_dot(t_player*	player, t_mlx_god*	god)
{
	mlx_pixel_put(god->mlx, god->win, player->x - 1, player->y - 1, 0xFFFF00);
	mlx_pixel_put(god->mlx, god->win, player->x + 1, player->y + 1, 0xFFFF00);
	mlx_pixel_put(god->mlx, god->win, player->x, player->y, 0xFFFF00);
	mlx_pixel_put(god->mlx, god->win, player->x - 1, player->y + 1, 0xFFFF00);
	mlx_pixel_put(god->mlx, god->win, player->x + 1, player->y - 1, 0xFFFF00);
}

void draw_map(t_mlx_god*	god)
{
	int i;
	int j;

	i = 0;
	printf("%d, %d\n", god->map_size_x, god->map_size_y);
	while (i < god->map_size_y)
	{
		j = 0;
		while (j < god->map_size_x)
		{
			if (god->map[i][j] == '1')
			{
				print_rectangle(god, j * god->map_size_y, i * god->map_size_x, 64, 64, 0xFF0000);
			}
			if (god->map[i][j] == '0')
			{
				print_rectangle(god, j * god->map_size_y, i * god->map_size_x, 64, 64, 0xFFFF00);
			}
			j++;
		}
		i++;
	}
}

void	print_rectangle(t_mlx_god*	god, int id_x, int id_y, int width, int heith, int colour)
{
	int i = id_x;

	while (i < id_x + width)
	{
		mlx_pixel_put(god->mlx, god->win, i, id_y, colour);
		mlx_pixel_put(god->mlx, god->win, i, id_y + heith, colour);
		i++;
	}
	i = id_y;
	while (i < id_y + heith)
	{
		mlx_pixel_put(god->mlx, god->win, id_x, i, colour);
		mlx_pixel_put(god->mlx, god->win, id_x + width, i, colour);
		i++;
	}
}

void	print_line(t_mlx_god*	god, int id_x, int id_y, int end_x, int end_y)
{
	double	dist;
	double	sin_a;
	double  cos_a;
	int		i = 0;

	dist = sqrt(pow(end_x - id_x, 2) + pow(end_y - id_y, 2));
	sin_a = dist / (end_y - id_y);
	cos_a = dist / (end_y - id_y);
	while ((double)i < dist)
	{
		mlx_pixel_put(god->mlx, god->win, (id_x + i * cos_a), (id_y + i * sin_a), 0xFF0000);
		i++;
	}
}

void	print_player_ray(t_mlx_god*	god, t_player* player)
{
	double	sin_a;
	double  cos_a;
	int		i = 0;

	sin_a = sin(player->angle);
	cos_a = cos(player->angle);
	while ((double)i < player->v_range)
	{
		mlx_pixel_put(god->mlx, god->win, (player->x + i * cos_a), (player->y + i * sin_a), 63743);
		i++;
	}
}
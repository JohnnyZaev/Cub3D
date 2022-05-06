/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/04/29 15:38:13 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

double	ft_norm(double ray_ang)
{
	ray_ang = remainder(ray_ang, 2 * M_PI);
	if (ray_ang < 0)
		ray_ang += 2 * M_PI;
	return (ray_ang);
}

int	is_wall(double y, double x, t_mlx_god *god)
{
	if (x >= 0 && x < (float)god->map_size_x * TAIL_SIZE && y >= 0
		&& y < (float)god->map_size_y * TAIL_SIZE)
	{
		if (god->map[(int)y / TAIL_SIZE][(int)x / TAIL_SIZE] != '1')
			return (1);
	}
	return (0);
}

double	distance_bew_points(double x, double y, double xd, double yd)
{
	return (sqrt(pow((xd - x), 2) + pow(yd - y, 2)));
}

int	esc(t_mlx_god *god)
{
	mlx_destroy_window(god->mlx, god->win);
	exit(0);
}

int	errors(int err)
{
	if (err == 1)
		printf("Malloc error\n");
	if (err == 2)
		printf("Mlx error\n");
	if (err == 3)
		printf("Arguments error\n");
	exit(err);
}

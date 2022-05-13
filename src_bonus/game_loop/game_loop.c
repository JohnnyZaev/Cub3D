/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:18:37 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/06 13:18:40 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static double	sin_cos_values(t_mlx_god *god, int flag)
{
	if (flag == 1)
		return (cos((god->player->angle + 90) * (M_PI / 180)));
	if (flag == 2)
		return (sin((god->player->angle + 90) * (M_PI / 180)));
	if (flag == 3)
		return (cos((god->player->angle) * (M_PI / 180)));
	if (flag == 4)
		return (sin((god->player->angle) * (M_PI / 180)));
	return (0);
}

static void	delta_movement_helper(t_mlx_god *god)
{
	if (god->keys->left)
	{
		if (is_wall(god->player->y - sin_cos_values(god, 2) \
		* (god->player->speed + 10), god->player->x - sin_cos_values(god, 1) \
		* (god->player->speed + 10), god))
		{
			god->player->x -= sin_cos_values(god, 1) * god->player->speed;
			god->player->y -= sin_cos_values(god, 2) * god->player->speed;
		}
	}
	if (god->keys->right)
	{
		if (is_wall(god->player->y + sin_cos_values(god, 2) \
		* (god->player->speed + 10), god->player->x + sin_cos_values(god, 1) \
		* (god->player->speed + 10), god))
		{
			god->player->x += sin_cos_values(god, 1) * god->player->speed;
			god->player->y += sin_cos_values(god, 2) * god->player->speed;
		}
	}
}

static void	delta_movement(t_mlx_god *god)
{
	delta_movement_helper(god);
	if (god->keys->back)
	{
		if (is_wall(god->player->y - sin_cos_values(god, 4) \
		* (god->player->speed + 10), god->player->x - sin_cos_values(god, 3) \
		* (god->player->speed + 10), god))
		{
			god->player->x -= sin_cos_values(god, 3) * god->player->speed;
			god->player->y -= sin_cos_values(god, 4) * god->player->speed;
		}
	}
	if (god->keys->forward)
	{
		if (is_wall(god->player->y + sin_cos_values(god, 4) \
		* (god->player->speed + 10), god->player->x + sin_cos_values(god, 3) \
		* (god->player->speed + 10), god))
		{
			god->player->x += sin_cos_values(god, 3) * god->player->speed;
			god->player->y += sin_cos_values(god, 4) * god->player->speed;
		}
	}
}

int	game_loop(t_mlx_god *god)
{
	if (god->keys->exit)
	{
		mlx_destroy_window(god->mlx, god->win);
		exit(0);
	}
	delta_movement(god);
	if (god->keys->rightr)
		god->player->angle -= 1;
	if (god->keys->leftr)
		god->player->angle += 1;
	mlx_destroy_image(god->mlx, god->img.img_ptr);
	mlx_clear_window(god->mlx, god->win);
	god->img.img_ptr = mlx_new_image(god->mlx, god->size_x, god->size_y);
	god->img.data = (int *)mlx_get_data_addr(god->img.img_ptr,
			&god->img.bpp, &god->img.size_line, &god->img.endian);
	drawrays(god);
	render3d(god);
	mlx_put_image_to_window(god->mlx, god->win, god->img.img_ptr, 0, 0);
	minimap_render(god, MINIMAP_SZ, MINIMAP_SZ);
	return (0);
}

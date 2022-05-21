/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_on_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:04:38 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/13 15:04:39 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->mm_data + (y * img->mm_size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	is_wall_ray(t_mlx_god *god, double x, double y)
{
	int	x_ed;
	int	y_ed;

	x_ed = (int)(x + god->player->x / TAIL_SIZE);
	y_ed = (int)(y + god->player->y / TAIL_SIZE);
	if (x_ed < 0 || y_ed < 0 || x_ed > god->map_size_x
		|| y_ed > god->map_size_y)
		return (1);
	if (god->map[y_ed][x_ed] == '1' || god->map[y_ed][x_ed] == ' ')
		return (1);
	return (0);
}

static double	get_max(t_mlx_god *god, t_minimap *mp, int j)
{
	if (god->player->angle < 0)
		mp->angle = 360 + (int)(god->player->angle - 30 + j * 30) % 360;
	else
		mp->angle = (int)(god->player->angle - 30 + j * 30) % 360;
	if ((abs((int)mp->angle) / 45) % 2 == 0)
	{
		if ((abs((int)mp->angle) > 135) && (abs((int)mp->angle) < 315))
			return ((MINIMAP_SZ * 10.5) / cos(((int) mp->angle % 45)
					* M_PI / 180));
		else
			return ((MINIMAP_SZ * 9.5) / cos(((int) mp->angle % 45)
					* M_PI / 180));
	}
	else
	{
		if ((abs((int)mp->angle) > 135) && (abs((int)mp->angle) < 315))
			return ((MINIMAP_SZ * 10.5) / cos((45 - (int) mp->angle % 45)
					* M_PI / 180));
		else
			return ((MINIMAP_SZ * 9.5) / cos((45 - (int) mp->angle % 45)
					* M_PI / 180));
	}
}

static void	draw_line(t_mlx_god *god, t_minimap *mp)
{
	int		i;
	int		j;
	double	max;

	j = 0;
	while (j < 3)
	{
		mp->cos = cos(god->player->angle * M_PI / 180 - M_PI / 6
				+ j * M_PI / 6);
		mp->sin = sin(god->player->angle * M_PI / 180 - M_PI / 6
				+ j * M_PI / 6);
		max = get_max(god, mp, j);
		i = 0;
		while (i < abs((int)max))
		{
			if (is_wall_ray(god, ((double) i / MINIMAP_SZ) * mp->cos,
					((double) i / MINIMAP_SZ) * mp->sin))
				break ;
			my_mlx_pixel_put(&god->img, mp->x + i * mp->cos,
				mp->y + i * mp->sin, RAY_COLOR);
			i++;
		}
		j++;
	}
}

void	draw_player(t_mlx_god *god, int initial_x, int initial_y)
{
	t_minimap	mp;

	mp.off_x = modf(god->player->x / TAIL_SIZE, &mp.x) * MINIMAP_SZ;
	mp.off_y = modf(god->player->y / TAIL_SIZE, &mp.y) * MINIMAP_SZ;
	mp.x = initial_x + (10 * MINIMAP_SZ) + mp.off_x;
	mp.y = initial_y + (10 * MINIMAP_SZ) + mp.off_y;
	draw_line(god, &mp);
	my_mlx_pixel_put(&god->img, (int)mp.x, (int)mp.y, PLAY_COLOR);
	my_mlx_pixel_put(&god->img, (int)mp.x + 1, (int)mp.y, PLAY_COLOR);
	my_mlx_pixel_put(&god->img, (int)mp.x - 1, (int)mp.y, PLAY_COLOR);
	my_mlx_pixel_put(&god->img, (int)mp.x, (int)mp.y + 1, PLAY_COLOR);
	my_mlx_pixel_put(&god->img, (int)mp.x, (int)mp.y - 1, PLAY_COLOR);
}

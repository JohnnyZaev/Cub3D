/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:53:17 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/10 12:53:20 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->mm_data + (y * img->mm_size_line + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	get_presice_color(char c)
{
	if (c == '1')
		return (WALL_COLOR);
	if (c == '0' || c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (ROOM_COLOR);
	return (0);
}

void	draw_square(t_mlx_god *god, int x, int y, int mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SZ)
	{
		j = 0;
		while (j < MINIMAP_SZ)
		{
			my_mlx_pixel_put(&god->img, x + i, y + j, mode);
			j++;
		}
		i++;
	}
}

void	draw_canvas(t_mlx_god *god, int initial_x, int initial_y)
{
	int	i;
	int	j;

	i = 0;
	while (i < 22 * MINIMAP_SZ)
	{
		j = 0;
		while (j < 22 * MINIMAP_SZ)
		{
			my_mlx_pixel_put(&god->img, i + initial_x - MINIMAP_SZ,
				j + initial_y - MINIMAP_SZ, 0);
			j++;
		}
		i++;
	}
}

void	minimap_render(t_mlx_god *god, int initial_x, int initial_y)
{
	int	i;
	int	j;
	int	h;
	int	k;

	god->img.mm_img_ptr = mlx_new_image(god->mlx, 220, 220);
	god->img.mm_data = mlx_get_data_addr(god->img.mm_img_ptr, &god->img.mm_bpp,
											 &god->img.mm_size_line, &god->img.mm_endian);
	i = (int)(god->player->x / TAIL_SIZE) - 10;
	j = (int)(god->player->y / TAIL_SIZE) - 10;
	draw_canvas(god, initial_x, initial_y);
	k = 0;
	while (j < god->map_size_y && k < 20)
	{
		i = (int)(god->player->x / TAIL_SIZE) - 10;
		h = 0;
		while (i < god->map_size_x && h < 20)
		{
			if (i >= 0 && j >= 0)
				draw_square(god, initial_x + h * MINIMAP_SZ, initial_y
					+ k * MINIMAP_SZ, get_presice_color(god->map[j][i]));
			i++;
			h++;
		}
		j++;
		k++;
	}
	draw_player(god, initial_x, initial_y);
	mlx_put_image_to_window(god->mlx, god->win, god->img.mm_img_ptr, initial_x, initial_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:08:39 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/06 12:08:41 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init(t_mlx_god *god, t_player *player)
{
	god->player = player;
	god->size_x = 0;
	god->size_y = 0;
	god->map_size_x = 0;
	god->map_size_y = 0;
	god->c_color = 0;
	god->f_color = 0;
	god->map = NULL;
	player->speed = 5;
}

void	set_textures(t_mlx_god *god)
{
	void	*img;
	int		tab[5];

	god->img.img_ptr = mlx_new_image(god->mlx, god->size_x, god->size_y);
	god->img.data = (int *)mlx_get_data_addr(god->img.img_ptr, &god->img.bpp,
			&god->img.size_line, &god->img.endian);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[1], &tab[0], &tab[1]);
	if (!img || !god->img.data)
	{
		printf("textures error\n");
		esc(god);
	}
	god->texturep[0] = (int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[3], &tab[0], &tab[1]);
	if (!img || !god->img.data)
	{
		printf("textures error\n");
		esc(god);
	}
	god->texturep[1] = (int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[0], &tab[0], &tab[1]);
	if (!img || !god->img.data)
	{
		printf("textures error\n");
		esc(god);
	}
	god->texturep[2] = (int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[2], &tab[0], &tab[1]);
	if (!img || !god->img.data)
	{
		printf("textures error\n");
		esc(god);
	}
	god->texturep[3] = (int *)mlx_get_data_addr(img, &tab[2], &tab[3], &tab[4]);
}

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

#include "cub3d.h"

//qTODO fix for norm



int		ecs(t_mlx_god *god)
{
	mlx_destroy_window(god->mlx, god->win);
	exit(0);
}

int		unhold(int key, t_keys *keys)
{
	if (key == ESC)
		keys->exit = false;
	if (key == RC_ROTATE)
		keys->rightr = false;
	if (key == CL_ROTATE)
		keys->leftr = false;
	if (key == LEFT)
		keys->left = false;
	if (key == RIGHT)
		keys->right = false;
	if (key == DOWN)
		keys->back = false;
	if (key == UP)
		keys->forward = false;
	return (0);
}

int		press(int key, t_keys *keys)
{
	if (key == ESC)
		keys->exit = true;
	if (key == RC_ROTATE)
		keys->rightr = true;
	if (key == CL_ROTATE)
		keys->leftr = true;
	if (key == LEFT)
		keys->left = true;
	if (key == RIGHT)
		keys->right = true;
	if (key == DOWN)
		keys->back = true;
	if (key == UP)
		keys->forward = true;
	return (0);
}

int		game_loop(t_mlx_god *god)
{
	if (god->keys->exit)
	{
		mlx_destroy_window(god->mlx, god->win);
		exit(0);
	}
	if (god->keys->left)
	{
		god->player->x -= cos((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
		god->player->y -= sin((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->right)
	{
		god->player->x += cos((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
		god->player->y += sin((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->back)
	{
		god->player->x -= cos((god->player->angle) * (M_PI / 180)) * god->player->speed;
		god->player->y -= sin((god->player->angle) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->forward)
	{
		god->player->x += cos((god->player->angle) * (M_PI / 180)) * god->player->speed;
		god->player->y += sin((god->player->angle) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->rightr)
		god->player->angle -= 3;
	if (god->keys->leftr)
		god->player->angle += 3;
	mlx_destroy_image(god->mlx, god->img.img_ptr);
	mlx_clear_window(god->mlx, god->win);
	god->img.img_ptr = mlx_new_image(god->mlx, god->size_x, god->size_y);
	god->img.data = (int *)mlx_get_data_addr(god->img.img_ptr,
											  &god->img.bpp, &god->img.size_line, &god->img.endian);
	drawrays(god);
	render3d(god);
	mlx_put_image_to_window(god->mlx, god->win, god->img.img_ptr, 0, 0);
	return (0);
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

void	set_textures(t_mlx_god *god)
{
	void	*img;
	int		tab[5];

	god->img.img_ptr = mlx_new_image(god->mlx, god->size_x, god->size_y);
	god->img.data = (int *)mlx_get_data_addr(god->img.img_ptr, &god->img.bpp,
											  &god->img.size_line, &god->img.endian);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[1], &tab[0], &tab[1]);
	if (!img || !god->img.data)
		ecs(god);
	god->texturep[0] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[3], &tab[0], &tab[1]);
	if (!img || !god->img.data)
		ecs(god);
	god->texturep[1] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[0], &tab[0], &tab[1]);
	if (!img || !god->img.data)
		ecs(god);
	god->texturep[2] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[2], &tab[0], &tab[1]);
	if (!img || !god->img.data)
		ecs(god);
	god->texturep[3] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
}

void	ft_init(t_mlx_god*	god, t_player* player)
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

int	main(int argc, char **argv)
{
	t_player	player;
	t_mlx_god	god;
	t_keys		keys;
	t_draws 	draws;
	t_render 	render;
	t_rays		*rays;

	ft_memset(&keys, false, sizeof(keys));
	god.draws = &draws;
	god.keys = &keys;
	god.render = &render;
	if (argc != 2)
	{
		printf("forgot something\n");
		return (1);
	}
	ft_init(&god, &player);
	if (parser(&god, argv[1]))
		return (1);
	mlx_get_screen_size(&god.size_x, &god.size_y);
	rays = malloc(sizeof(t_rays) * god.size_x);
	god.rays = rays;
	god.mlx = mlx_init();
	if (!god.mlx)
		errors(2);
	god.win = mlx_new_window(god.mlx, god.size_x, god.size_y, "Cub3D");
	set_textures(&god);
	mlx_hook(god.win, 17, 0, ecs, &god);
	mlx_hook(god.win, 2, 0, press, (&god)->keys);
	mlx_hook(god.win, 3, 0, unhold, (&god)->keys);
	mlx_loop_hook(god.mlx, game_loop, &god);
	mlx_loop(god.mlx);
}

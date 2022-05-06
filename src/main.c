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

int	ecs(t_mlx_god *god)
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
		errors(3);
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

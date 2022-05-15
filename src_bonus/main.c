/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/05/15 15:12:15 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	mouse_move(int x, int y, t_mlx_god *god)
{
	int	resolution_part;

	resolution_part = god->size_x / 5;
	(void)y;
	if (x > 0 && x < resolution_part)
		god->keys->rightr = true;
	else if (x > god->size_x - resolution_part)
		god->keys->leftr = true;
	else
	{
		god->keys->rightr = false;
		god->keys->leftr = false;
	}
	return (0);
}

static void	mlx_start(t_mlx_god *god)
{
	t_rays		*rays;

	mlx_get_screen_size(&god->size_x, &god->size_y);
	rays = malloc(sizeof(t_rays) * god->size_x);
	god->rays = rays;
	god->mlx = mlx_init();
	if (!god->mlx)
		errors(2);
	god->win = mlx_new_window(god->mlx, god->size_x, god->size_y, "Cub3D");
	set_textures(god);
	mlx_hook(god->win, 17, 0, &esc, god);
	mlx_hook(god->win, 2, 0, &press, god->keys);
	mlx_hook(god->win, 3, 0, &unhold, god->keys);
	mlx_hook(god->win, 6, 0, &mouse_move, god);
	mlx_loop_hook(god->mlx, &game_loop, god);
	mlx_loop(god->mlx);
}

int	main(int argc, char **argv)
{
	t_player	player;
	t_mlx_god	god;
	t_keys		keys;
	t_draws		draws;
	t_render	render;

	ft_memset(&keys, false, sizeof(keys));
	god.draws = &draws;
	god.keys = &keys;
	god.render = &render;
	if (argc != 2 || ft_strlen(argv[1]) < 4)
		errors(3);
	ft_init(&god, &player);
	if (parser(&god, argv[1]))
		return (1);
	mlx_start(&god);
}

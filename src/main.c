/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/04/13 16:45:16 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ft_key_action(int keycode, t_mlx_god*	god)
{
	double sin_a;
	double cos_a;

	sin_a = sin(god->player->angle);
	cos_a = cos(god->player->angle);
	if (keycode == UP)
	{
		god->player->x += god->player->speed * cos_a;
		god->player->y += god->player->speed * sin_a;
	}
	else if (keycode == DOWN)
	{
		god->player->x += -god->player->speed * cos_a;
		god->player->y += -god->player->speed * sin_a;
	}
	else if (keycode == LEFT)
	{
		god->player->x += god->player->speed * sin_a;
		god->player->y += -god->player->speed * cos_a;
	}
	else if (keycode == RIGHT)
	{
		god->player->x += -god->player->speed * sin_a;
		god->player->y += god->player->speed * cos_a;
	}
	else if (keycode == RC_ROTATE)
	{
		god->player->angle -= 0.05;
	}
	else if (keycode == CL_ROTATE)
	{
		god->player->angle += 0.05;
	}
	mlx_clear_window(god->mlx, god->win);
	print_player_dot(god->player, god);
	print_player_ray(god, god->player);
	return (1);
}

void	ft_init(t_mlx_god*	god, t_player* player)
{
	god->player = player;
	god->size_x = 0;
	god->size_y = 0;
	god->c_color = 0;
	god->f_color = 0;
	god->map = NULL;
	player->v_range = 150;
	player->speed = 5;
}

int	main(int argc, char **argv)
{
	t_player	player;
	t_mlx_god	god;
	int i = 0;

	(void)argv;
	if (argc != 2)
	{
		printf("forgot something\n");
		return 1;
	}
	ft_init(&god, &player);
	parser(&god, argv[1]);
	god.mlx = mlx_init();
	god.win = mlx_new_window(god.mlx, 1000, 1000, "Cub3D");
	if (god.map)
	{
		while (god.map[i])
			printf("%s\n", god.map[i++]);
	}
	printf("floor - %d\nceilling - %d\n", god.f_color, god.c_color);
	printf("textures:\n%s\n%s\n%s\n", god.textures[0], god.textures[1], god.textures[2]);
	mlx_hook(god.win, 2, 0, ft_key_action, &god);
	mlx_loop(god.mlx);
}

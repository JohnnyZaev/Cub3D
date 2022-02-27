/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/27 19:42:09 by gvarys           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;

	(void)argv;
	if (argc != 2)
		errors(3);
	mlx = mlx_init();
	if (!mlx)
		errors(2);
	mlx_get_screen_size(&size_x, &size_y);
	win = mlx_new_window(mlx, size_x, size_y, "cub3D");
	mlx_loop(mlx);
	return (0);
}

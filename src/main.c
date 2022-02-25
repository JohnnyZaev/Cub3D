/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/25 16:18:33 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	int		size_x;
	int		size_y;
	(void)argc;
	(void)argv;

	mlx = mlx_init();
	mlx_get_screen_size(&size_x, &size_y);
	win = mlx_new_window(mlx, size_x, size_y, "cub3D");
	mlx_loop(mlx);
	return (0);
}
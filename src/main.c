/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:21:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/25 15:46:26 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;
	(void)argc;
	(void)argv;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	mlx_loop(mlx);
	return (0);
}
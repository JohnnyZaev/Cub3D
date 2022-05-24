/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:49:24 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/15 14:58:40 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	if_player(t_mlx_god *god, char point, int i, int j)
{
	double	stuck_helper;

	stuck_helper = 0;
	if (point == 'N')
	{
		god->player->angle = 270;
		stuck_helper = 0.5;
	}
	else if (point == 'S')
	{
		god->player->angle = 90;
		stuck_helper = 0.5;
	}
	else if (point == 'E')
	{
		god->player->angle = 0;
		stuck_helper = 0.5;
	}
	else if (point == 'W')
	{
		god->player->angle = 180;
		stuck_helper = 0.5;
	}
	god->player->x = (j + stuck_helper) * TAIL_SIZE;
	god->player->y = (i + stuck_helper) * TAIL_SIZE;
}

static int	if_void(t_mlx_god *god, int i, int j)
{
	if ((i == 0 || j == 0 || i == god->map_size_y - 1 || \
		j == god->map_size_x - 2))
		return (1);
	if (god->map[i - 1][j] == ' ' || \
		god->map[i + 1][j] == ' ' || \
		god->map[i][j - 1] == ' ' || \
		god->map[i][j + 1] == ' ')
		return (1);
	return (0);
}

static int	loop_body(t_mlx_god *god, int i, int j, int *flag)
{
	if (god->map[i][j] == 'N' || god->map[i][j] == 'S'
		|| god->map[i][j] == 'E' || god->map[i][j] == 'W')
	{
		if (*flag == 1 || if_void(god, i, j))
			return (1);
		*flag = 1;
		if_player(god, god->map[i][j], i, j);
	}
	else if (god->map[i][j] == '0')
	{
		if (if_void(god, i, j))
			return (1);
	}
	else if (god->map[i][j] != '1' && god->map[i][j] != ' ')
		return (1);
	return (0);
}

int	check_map(t_mlx_god *god)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (god->map[i])
	{
		j = 0;
		while (god->map[i][j])
		{
			if (loop_body(god, i, j, &flag))
				return (1);
			j++;
		}
		i++;
	}
	if (!flag)
		return (1);
	return (0);
}

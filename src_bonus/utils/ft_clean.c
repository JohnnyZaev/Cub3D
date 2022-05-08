/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:54:37 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/04 16:56:09 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	unhold(int key, t_keys *keys)
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

int	press(int key, t_keys *keys)
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

void	ft_clean(t_mlx_god *god, int mode)
{
	int	i;

	i = 0;
	if ((mode & 1) && god->map)
	{
		while (god->map[i])
		{
			free(god->map[i]);
			god->map[i++] = NULL;
		}
		free(god->map);
		god->map = NULL;
	}
	i = 0;
	if (!(mode & 2))
		return ;
	while (i < 4)
	{
		if (god->textures[i])
		{
			free(god->textures[i]);
			god->textures[i] = NULL;
		}
		i++;
	}
}

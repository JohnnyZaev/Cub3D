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

#include "cub3d.h"

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

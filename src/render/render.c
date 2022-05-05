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

static void	renha(t_mlx_god *god)
{
	god->render->distancetop = god->render->j - god->render->top;
	god->txty = (int)(god->render->distancetop
			* ((float) TAIL_SIZE / god->render->wallstrip));
	if (god->render->i >= 0 && god->render->i < god->size_x
		&& god->render->j >= 0 && god->render->j < god->size_y)
	{
		if (god->rays[god->render->i].hitvert
			&& god->rays[god->render->i].right)
			god->img.data[(int)god->render->i + (int)god->render->j * god->size_x]
			= (god->texturep[0][TAIL_SIZE * god->txty + god->txtx]);
		if (god->rays[god->render->i].hitvert && god->rays[god->render->i].left)
			god->img.data[(int)god->render->i + (int)god->render->j * god->size_x] =
					god->texturep[1][TAIL_SIZE * god->txty + god->txtx];
		if (!god->rays[god->render->i].hitvert && god->rays[god->render->i].up)
			god->img.data[(int)god->render->i + (int)god->render->j * god->size_x] =
					god->texturep[2][TAIL_SIZE * god->txty + god->txtx];
		if (!god->rays[god->render->i].hitvert && god->rays[god->render->i].down)
			god->img.data[(int)god->render->i + (int)god->render->j * god->size_x] =
					god->texturep[3][TAIL_SIZE * god->txty + god->txtx];
	}
}

static void		renhel(t_mlx_god *god)
{
	god->render->raydist = god->rays[god->render->i].distance *
						   cos(god->rays[god->render->i].angle - (god->player->angle * (M_PI/180)));
	god->render->wallstrip = (TAIL_SIZE / god->render->raydist) * god->render->distpj;
	god->render->top = ((float)god->size_y / 2) - (god->render->wallstrip / 2);
	god->render->bottom = god->render->top + god->render->wallstrip;
	god->render->j = 0;
	if (god->rays[god->render->i].hitvert)
		god->txtx = ((int)god->rays[god->render->i].wallhy) % TAIL_SIZE;
	else
		god->txtx = ((int)god->rays[god->render->i].wallhx) % TAIL_SIZE;
	while (god->render->j < god->render->top)
	{
		god->render->distancetop = god->render->j - god->render->top;
		god->txty = (int)((float)TAIL_SIZE / god->render->wallstrip * god->render->distancetop)
					& (TAIL_SIZE - 1);
		if (god->render->i >= 0 && god->render->i < god->size_x && god->render->j >= 0 && god->render->j < god->size_y)
			god->img.data[(int)god->render->i + (int)god->render->j * god->size_x] =
					god->c_color;
		god->render->j++;
	}
}

void		render3d(t_mlx_god *god)
{
	god->render->i = 0;
	god->render->distpj = ((float)god->size_x / 2) / (tan((30 * (M_PI/180))));
	while (god->render->i < god->size_x)
	{
		renhel(god);
		while (god->render->j < god->render->bottom)
		{
			renha(god);
			god->render->j++;
		}
		while (god->render->j < god->size_y)
		{
			god->render->distancetop = god->render->j - god->render->top;
			god->txty = (int)((float)TAIL_SIZE / god->render->wallstrip * god->render->distancetop)
						& (TAIL_SIZE - 1);
			if (god->render->i >= 0 && god->render->i < god->size_x && god->render->j >= 0 &&
				god->render->j < god->size_y)
				god->img.data[(int)god->render->i + (int)god->render->j * god->size_x] =
						god->f_color;
			god->render->j++;
		}
		god->render->i++;
	}
}
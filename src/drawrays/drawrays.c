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

static void	ft_help_one(t_mlx_god *god)
{
	while (god->draws->nhorx >= 0 && god->draws->nhorx <= god->map_size_x
		* TAIL_SIZE && god->draws->nhory >= 0 && god->draws->nhory
		<= god->map_size_y * TAIL_SIZE)
	{
		if (!(is_wall(god->draws->nhory
					- god->draws->tocheck, god->draws->nhorx, god)))
		{
			god->draws->fhwhit = 1;
			god->draws->hwhitx = god->draws->nhorx;
			god->draws->hwhity = god->draws->nhory;
			break ;
		}
		else
		{
			god->draws->nhorx += god->draws->xsps;
			god->draws->nhory += god->draws->ysps;
		}
	}
}

static void	ft_halfone(int i, t_mlx_god *god)
{
	god->draws->fhwhit = 0;
	god->draws->vwallhit = 0;
	god->draws->rayang = ft_norm(god->draws->rayang);
	god->rays[i].down = (god->draws->rayang > 0) && (god->draws->rayang < M_PI);
	god->rays[i].up = !god->rays[i].down;
	god->rays[i].right = (god->draws->rayang < (0.5 * M_PI))
		|| god->draws->rayang > 1.5 * M_PI;
	god->rays[i].left = !god->rays[i].right;
	god->draws->tocheck = god->rays[i].up;
	god->draws->yint = floor((god->player->y / TAIL_SIZE)) * TAIL_SIZE;
	if (god->rays[i].down)
		god->draws->yint += TAIL_SIZE;
	god->draws->xint = god->player->x - ((god->player->y
				- god->draws->yint) / tan(god->draws->rayang));
	god->draws->ysps = TAIL_SIZE;
	if (god->rays[i].up)
		god->draws->ysps *= -1;
	god->draws->xsps = god->draws->ysps / tan(god->draws->rayang);
	god->draws->nhorx = god->draws->xint;
	god->draws->nhory = god->draws->yint;
	ft_help_one(god);
}

static void	ft_halftwo(int i, t_mlx_god *god)
{
	god->draws->tocheck = god->rays[i].left;
	god->draws->xint = floor(god->player->x / TAIL_SIZE) * TAIL_SIZE;
	if (god->rays[i].right)
		god->draws->xint += TAIL_SIZE;
	god->draws->yint = god->player->y - (god->player->x - god->draws->xint)
		* tan(god->draws->rayang);
	god->draws->xsps = TAIL_SIZE;
	if (god->rays[i].left)
		god->draws->xsps *= -1;
	god->draws->ysps = god->draws->xsps * tan(god->draws->rayang);
	god->draws->nhorx = god->draws->xint;
	god->draws->nhory = god->draws->yint;
	while (god->draws->nhorx >= 0 && god->draws->nhorx <= god->map_size_x
		* TAIL_SIZE && god->draws->nhory >= 0 && god->draws->nhory
		<= god->map_size_y * TAIL_SIZE)
	{
		if (!(is_wall(god->draws->nhory, god->draws->nhorx
					- god->draws->tocheck, god)))
		{
			god->draws->vwallhit = 1;
			god->draws->vwhitx = god->draws->nhorx;
			god->draws->vwhity = god->draws->nhory;
			break ;
		}
		else
		{
			god->draws->nhorx += god->draws->xsps;
			god->draws->nhory += god->draws->ysps;
		}
	}
}

void	drawrays(t_mlx_god *god)
{
	int		i;

	god->draws->fhwhit = 0;
	god->draws->vwallhit = 0;
	god->draws->rayang = (god->player->angle - 30) * (M_PI / 180);
	i = -1;
	while (++i < god->size_x)
	{
		ft_halfone(i, god);
		ft_halftwo(i, god);
		if (god->draws->fhwhit)
			god->draws->hdistnc = distance_bew_points(god->player->x, \
			god->player->y, god->draws->hwhitx, god->draws->hwhity);
		else
			god->draws->hdistnc = INT32_MAX;
		if (god->draws->vwallhit)
			god->draws->vdistnc = distance_bew_points(god->player->x, god->player->y, god->draws->vwhitx, god->draws->vwhity);
		else
			god->draws->vdistnc = INT32_MAX;
		god->rays[i].wallhx = (god->draws->hdistnc
				< god->draws->vdistnc) ? god->draws->hwhitx : god->draws->vwhitx;
		god->rays[i].wallhy = (god->draws->hdistnc
				< god->draws->vdistnc) ? god->draws->hwhity : god->draws->vwhity;
		god->rays[i].distance = (god->draws->hdistnc < god->draws->vdistnc) ?
								god->draws->hdistnc : god->draws->vdistnc;
		god->rays[i].angle = god->draws->rayang;
		god->rays[i].hitvert = (god->draws->vdistnc < god->draws->hdistnc);
		god->draws->rayang += (60 * (M_PI / 180)) / god->size_x;
	}
}

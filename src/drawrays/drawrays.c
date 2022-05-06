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

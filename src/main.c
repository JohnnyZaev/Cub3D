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

//TODO fix for norm
void		ft_renha(t_mlx_god *god)
{
	god->render->distancetop = god->render->j - god->render->top;
	god->txty = (god->render->distancetop) * ((float)TAIL_SIZE / god->render->wallstrip);
	if (god->render->i >= 0 && god->render->i < god->size_x && god->render->j >= 0 && god->render->j < god->size_y)
	{
		if (god->rays[god->render->i].hitvert && god->rays[god->render->i].right)
			god->img.data[(int)god->render->i + (int)god->render->j * god->size_x] =
					(god->texturep[0][TAIL_SIZE * god->txty + god->txtx]);
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

void		ft_renhel(t_mlx_god *god)
{
	god->render->raydist = god->rays[god->render->i].distance *
				cosf(god->rays[god->render->i].angle - (god->player->angle * CONV));
	god->render->wallstrip = (TAIL_SIZE / god->render->raydist) * god->render->distpj;
	god->render->top = (god->size_y / 2) - (god->render->wallstrip / 2);
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
void		ft_render3d(t_mlx_god *god)
{
	god->render->i = 0;
	god->render->distpj = (god->size_x / 2) / (tan((30 * CONV)));
	while (god->render->i < god->size_x)
	{
		ft_renhel(god);
		while (god->render->j < god->render->bottom)
		{
			ft_renha(god);
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
//////////////////////////////////////////////////////////////////////////////////////////////////////
float	ft_norm(float rayang)
{
	rayang = remainder(rayang, 2 * M_PI);
	rayang += rayang < 0 ? 2 * M_PI : 0;
	return (rayang);
}

int		ft_iswal(float y, float x, t_mlx_god *god)
{
	if (x >= 0 && x < god->map_size_x * TAIL_SIZE && y >= 0 &&
		y < god->map_size_y * TAIL_SIZE)
	{
		if (god->map[(int)y / TAIL_SIZE][(int)x / TAIL_SIZE] != '1')
			return (1);
	}
	return (0);
}

double		distance_bew_points(float x, float y, float xd, float yd)
{
	return (sqrt(pow((xd - x), 2) + pow(yd - y, 2)));
}

void		ft_helpone(t_mlx_god *god)
{
	while (god->draws->nhorx >= 0 && god->draws->nhorx <= god->map_size_x * TAIL_SIZE &&
			god->draws->nhory >= 0 && god->draws->nhory <= god->map_size_y * TAIL_SIZE)
	{
		if (!(ft_iswal(god->draws->nhory -
							   god->draws->tocheck, god->draws->nhorx, god)))
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

void		ft_halfone(int i, t_mlx_god *god)
{
	god->draws->fhwhit = 0;
	god->draws->vwallhit = 0;
	god->draws->rayang = ft_norm(god->draws->rayang);
	god->rays[i].down = (god->draws->rayang > 0) && (god->draws->rayang < M_PI);
	god->rays[i].up = !god->rays[i].down;
	god->rays[i].right = (god->draws->rayang < (0.5 * M_PI)) ||
					  (god->draws->rayang > 1.5 * M_PI);
	god->rays[i].left = !god->rays[i].right;
	god->draws->tocheck = god->rays[i].up ? 1 : 0;
	god->draws->yint = floor((god->player->y / TAIL_SIZE)) * TAIL_SIZE;
	god->draws->yint += (god->rays[i].down) ? TAIL_SIZE : 0;
	god->draws->xint = god->player->x - ((god->player->y - god->draws->yint) / tan(god->draws->rayang));
	god->draws->ysps = TAIL_SIZE;
	god->draws->ysps *= (god->rays[i].up) ? -1 : 1;
	god->draws->xsps = god->draws->ysps / tan(god->draws->rayang);
	god->draws->nhorx = god->draws->xint;
	god->draws->nhory = god->draws->yint;
	ft_helpone(god);
}

void		ft_halftwo(int i, t_mlx_god *god)
{
	god->draws->tocheck = god->rays[i].left ? 1 : 0;
	god->draws->xint = floor(god->player->x / TAIL_SIZE) * TAIL_SIZE;
	god->draws->xint += god->rays[i].right ? TAIL_SIZE : 0;
	god->draws->yint = god->player->y - (god->player->x - god->draws->xint) * tan(god->draws->rayang);
	god->draws->xsps = TAIL_SIZE;
	god->draws->xsps *= god->rays[i].left ? -1 : 1;
	god->draws->ysps = god->draws->xsps * tan(god->draws->rayang);
	god->draws->nhorx = god->draws->xint;
	god->draws->nhory = god->draws->yint;
	while (god->draws->nhorx >= 0 && god->draws->nhorx <= god->map_size_x * TAIL_SIZE &&
			god->draws->nhory >= 0 && god->draws->nhory <= god->map_size_y * TAIL_SIZE)
	{
		if (!(ft_iswal(god->draws->nhory, god->draws->nhorx - god->draws->tocheck, god)))
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

void		drawrays(t_mlx_god *god)
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
		god->draws->hdistnc = (god->draws->fhwhit) ? distance_bew_points(god->player->x, god->player->y,
																		 god->draws->hwhitx, god->draws->hwhity) : INT32_MAX;
		god->draws->vdistnc = (god->draws->vwallhit)
						  ? distance_bew_points(god->player->x, god->player->y, god->draws->vwhitx, god->draws->vwhity)
						  : INT32_MAX;
		god->rays[i].wallhx = (god->draws->hdistnc <
				god->draws->vdistnc) ? god->draws->hwhitx : god->draws->vwhitx;
		god->rays[i].wallhy = (god->draws->hdistnc <
				god->draws->vdistnc) ? god->draws->hwhity : god->draws->vwhity;
		god->rays[i].distance = (god->draws->hdistnc < god->draws->vdistnc) ?
							 god->draws->hdistnc : god->draws->vdistnc;
		god->rays[i].angle = god->draws->rayang;
		god->rays[i].hitvert = (god->draws->vdistnc < god->draws->hdistnc);
		god->draws->rayang += (60 * (M_PI / 180)) / god->size_x;
	}
}

int		ecs(t_mlx_god *god)
{
	mlx_destroy_window(god->mlx, god->win);
	exit(0);
}

int		unpress(int key, t_keys *keys)
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

int		press(int key, t_keys *keys)
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

int		game_loop(t_mlx_god *god)
{
	if (god->keys->exit)
	{
		mlx_destroy_window(god->mlx, god->win);
		exit(0);
	}
	if (god->keys->left)
	{
		god->player->x -= cos((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
		god->player->y -= sin((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->right)
	{
		god->player->x += cos((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
		god->player->y += sin((god->player->angle + 90) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->back)
	{
		god->player->x -= cos((god->player->angle) * (M_PI / 180)) * god->player->speed;
		god->player->y -= sin((god->player->angle) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->forward)
	{
		god->player->x += cos((god->player->angle) * (M_PI / 180)) * god->player->speed;
		god->player->y += sin((god->player->angle) * (M_PI / 180)) * god->player->speed;
	}
	if (god->keys->rightr)
		god->player->angle -= 3;
	if (god->keys->leftr)
		god->player->angle += 3;
	mlx_destroy_image(god->mlx, god->img.img_ptr);
	mlx_clear_window(god->mlx, god->win);
	god->img.img_ptr = mlx_new_image(god->mlx, god->size_x, god->size_y);
	god->img.data = (int *)mlx_get_data_addr(god->img.img_ptr,
											  &god->img.bpp, &god->img.size_line, &god->img.endian);
	drawrays(god);
	///////////////////////////////////////////////////
	ft_render3d(god);
	///////////////////////////////////////////////////
	mlx_put_image_to_window(god->mlx, god->win, god->img.img_ptr, 0, 0);
	return (0);
}

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

void	set_textures(t_mlx_god *god)
{
	void	*img;
	int		tab[5];

	god->img.img_ptr = mlx_new_image(god->mlx, god->size_x, god->size_y);
	god->img.data = (int *)mlx_get_data_addr(god->img.img_ptr, &god->img.bpp,
											  &god->img.size_line, &god->img.endian);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[1], &tab[0], &tab[1]);
	if (!img)
		ecs(god);
	god->texturep[0] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[3], &tab[0], &tab[1]);
	if (!img)
		ecs(god);
	god->texturep[1] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[0], &tab[0], &tab[1]);
	if (!img)
		ecs(god);
	god->texturep[2] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
	img = mlx_xpm_file_to_image(god->mlx, god->textures[2], &tab[0], &tab[1]);
	if (!img)
		ecs(god);
	god->texturep[3] = (int *)mlx_get_data_addr(img,
												 &tab[2], &tab[3], &tab[4]);
}

void	ft_init(t_mlx_god*	god, t_player* player)
{
	god->player = player;
	god->size_x = 0;
	god->size_y = 0;
	god->map_size_x = 0;
	god->map_size_y = 0;
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
	t_keys		keys;
	t_draws 	draws;
	t_render 	render;
	t_rays		*rays;

	memset(&keys, false, sizeof(keys));
	god.draws = &draws;
	god.keys = &keys;
	god.render = &render;
	if (argc != 2)
	{
		printf("forgot something\n");
		return (1);
	}
	ft_init(&god, &player);
	parser(&god, argv[1]);
	mlx_get_screen_size(&god.size_x, &god.size_y);
	rays = malloc(sizeof(t_rays) * god.size_x);
	god.rays = rays;
	god.mlx = mlx_init();
	god.win = mlx_new_window(god.mlx, god.size_x, god.size_y, "Cub3D");
	set_textures(&god);
	mlx_hook(god.win, 17, 0, ecs, &god);
	mlx_hook(god.win, 2, 0, press, (&god)->keys);
	mlx_hook(god.win, 3, 0, unpress, (&god)->keys);
	mlx_loop_hook(god.mlx, game_loop, &god);
	mlx_loop(god.mlx);
}

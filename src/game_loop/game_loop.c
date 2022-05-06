#include "cub3d.h"

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

int	game_loop(t_mlx_god *god)
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
	render3d(god);
	mlx_put_image_to_window(god->mlx, god->win, god->img.img_ptr, 0, 0);
	return (0);
}
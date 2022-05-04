#include "cub3d.h"

double	ft_norm(double ray_ang)
{
	ray_ang = remainder(ray_ang, 2 * M_PI);
	ray_ang += ray_ang < 0 ? 2 * M_PI : 0;
	return (ray_ang);
}

int		is_wall(double y, double x, t_mlx_god *god)
{
	if (x >= 0 && x < (float)god->map_size_x * TAIL_SIZE && y >= 0 &&
		y < (float)god->map_size_y * TAIL_SIZE)
	{
		if (god->map[(int)y / TAIL_SIZE][(int)x / TAIL_SIZE] != '1')
			return (1);
	}
	return (0);
}

double		distance_bew_points(double x, double y, double xd, double yd)
{
	return (sqrt(pow((xd - x), 2) + pow(yd - y, 2)));
}

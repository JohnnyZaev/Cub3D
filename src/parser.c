/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:21:56 by ereginia          #+#    #+#             */
/*   Updated: 2022/04/13 17:04:49 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int find_symbols(const char *str, const char *find)
{
	int i = 0;
	int j = 0;

	if (str[0] == '\n')
		return (1);
	while (str[i])
	{
		while (str[i] && str[i] != '\n' && find[j])
		{
			if (str[i] != find[j])
			{
				j++;
				if (j == (int)ft_strlen(find))
					return (1);
				continue;
			}
			i++;
			j = 0;
		}
		i++;
	}
	return (0);
}

int room_for_map(t_mlx_god* god, char *file_name)
{
	int		fd;
	int		i = 0;
	char	*str;

	if (parse_textures_and_color(god, file_name, &fd))
		return (1);
	str = get_next_line(fd);
	while (str && !ft_strncmp(str, "\n", 1))
	{
		free(str);
		str = get_next_line(fd);
	}
	if (find_symbols(str, " 01NSEW"))
		return (1);
	while (str)
	{
		if (god->size_x < (int)ft_strlen(str))
			god->size_x = (int)ft_strlen(str);
		god->size_y++;
		free(str);
		str = get_next_line(fd);
	}
	god->map = (char **)malloc(sizeof(char *) * god->size_y + 1);
	while (i < god->size_y)
	{
		god->map[i] = (char *)malloc(sizeof(char) * (god->size_x + 1));
		ft_memset(god->map[i], ' ', sizeof(char) * (god->size_x + 1));
		god->map[i][god->size_x] = '\0';
		i++;
	}
	god->map[i] = NULL;
	close(fd);
	return (0);
}

void fill_map(t_mlx_god* god, char *file_name)
{
	char	*str;
	int		fd;
	int		i = 0;
	int		j = 0;

	fd = open(file_name, O_RDONLY, 0644);
	str = get_next_line(fd);
	while (find_symbols(str, " 01NSEW"))
	{
		free(str);
		str = get_next_line(fd);
	}
	while (str)
	{
		j = 0;
		while (str[j] && str[j] != '\n')
		{
			god->map[i][j] = str[j];
			j++;
		}
		free(str);
		str = get_next_line(fd);
		i++;
	}
}

int	check_map(t_mlx_god* god)
{
	int i = 0;
	int j = 0;
	int flag = 0;

	while (god->map[i])
	{
		j = 0;
		while (god->map[i][j])
		{
			if (god->map[i][j] == 'N' || god->map[i][j] == 'S'
					|| god->map[i][j] == 'E' || god->map[i][j] == 'W')
			{
				if (flag == 1)
					return (1);
				flag = 1;
				if (god->map[i][j] == 'N')
					god->player->angle =  3 * M_PI / 2;
				else if (god->map[i][j] == 'S')
					god->player->angle =  M_PI / 2;
				else if (god->map[i][j] == 'E')
					god->player->angle = 0;
				else if (god->map[i][j] == 'W')
					god->player->angle = M_PI;
				god->player->x = i * 10;
				god->player->y = j * 10;
			}
			else if (god->map[i][j] == '0')
			{
				if ((i > 0 && god->map[i - 1][j] == ' ') || \
					(i < god->size_x &&  god->map[i + 1][j] == ' ') || \
					(j > 0 && god->map[i][j - 1] == ' ') || \
					(j < god->size_y && god->map[i][j + 1] == ' ') || \
					(i == 0 || j == 0 || i == god->size_y || j == god->size_x))
					return 1;
			}
			else if (god->map[i][j] != '1' && god->map[i][j] != ' ')
				return 1;
			j++;
		}
		i++;
	}
	if (!flag)
		return 1;
	return 0;
}

void	parser(t_mlx_god* god, char *file_name)
{
	if (room_for_map(god, file_name))
	{
		printf("error: invalid elements\n");
		ft_clean(god, 2);
		return ;
	}
	fill_map(god, file_name);
	if (check_map(god))
	{
		printf("error: sorry but this map incorrect\n");
		ft_clean(god, 3);
	}
}
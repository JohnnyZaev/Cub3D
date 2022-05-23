/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:21:56 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/15 14:59:28 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	find_symbols(const char *str, const char *find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
				continue ;
			}
			i++;
			j = 0;
		}
		i++;
	}
	return (0);
}

static void	room_creation(t_mlx_god *god)
{
	int	i;

	god->map = (char **)malloc(sizeof(char *) * god->map_size_y + 1);
	i = 0;
	while (i < god->map_size_y)
	{
		god->map[i] = (char *)malloc(sizeof(char) * (god->map_size_x + 1));
		ft_memset(god->map[i], ' ', sizeof(char) * (god->map_size_x + 1));
		god->map[i][god->map_size_x] = '\0';
		i++;
	}
	god->map[i] = NULL;
}

int	room_for_map(t_mlx_god *god, char *file_name)
{
	int		fd;
	char	*str;

	if (parse_textures_and_color(god, file_name, &fd))
		return (1);
	str = get_next_line(fd);
	while (str && !ft_strncmp(str, "\n", 1))
	{
		free(str);
		str = get_next_line(fd);
	}
	if (str == NULL || find_symbols(str, " 01NSEW"))
		return (1);
	while (str)
	{
		if (god->map_size_x < (int)ft_strlen(str))
			god->map_size_x = (int)ft_strlen(str);
		god->map_size_y++;
		free(str);
		str = get_next_line(fd);
	}
	room_creation(god);
	close(fd);
	return (0);
}

void	fill_map(t_mlx_god *god, char *file_name)
{
	char	*str;
	int		fd;
	int		i;
	int		j;

	fd = open(file_name, O_RDONLY, 0644);
	str = get_next_line(fd);
	while (find_symbols(str, " 01NSEW"))
	{
		free(str);
		str = get_next_line(fd);
	}
	i = 0;
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

int	parser(t_mlx_god *god, char *file_name)
{
	char	*buf;

	if (room_for_map(god, file_name))
	{
		printf("error: invalid elements\n");
		ft_clean(god, 2);
		return (1);
	}
	buf = ft_substr(file_name, ft_strlen(file_name) - 4, 4);
	if (ft_strncmp(buf, ".cub", 4))
	{
		printf("error: map.cub extension\n");
		ft_clean(god, 2);
		free(buf);
		return (1);
	}
	free(buf);
	fill_map(god, file_name);
	if (check_map(god))
	{
		printf("error: sorry but this map.cub incorrect\n");
		ft_clean(god, 3);
		return (1);
	}
	return (0);
}

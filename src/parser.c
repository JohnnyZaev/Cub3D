/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:21:56 by ereginia          #+#    #+#             */
/*   Updated: 2022/04/12 17:31:44 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int parse_color(t_mlx_god* god, char *str, char flag)
{
	char	*buf;
	int		i = 0;
	int		j = 0;

	while (j < 3)
	{
		buf = ft_itoa(ft_atoi(&str[i]));
		if (ft_atoi(buf) < 0 || ft_atoi(buf) > 255)
		    return (1);
		while (str[i] == ' ')
		    i++;
		if (ft_strncmp(buf, &str[i], ft_strlen(buf)))
			return (1);
		if (flag == 0)
		{
			god->f_color *= 256;
			god->f_color += ft_atoi(buf);
		}
		else if (flag == 1)
		{
			god->c_color *= 256;
			god->c_color += ft_atoi(buf);
		}
		while (str[i] == ' ')
		    i++;
		i += ft_strlen(buf);
		free(buf);
		buf = &str[i];
		while (str[i] == ' ')
		    i++;
		if ((str[i] != ',' && j != 2) || (j == 2 && str[i] != '\n'))
		    return 1;
		j++;
		i++;
	}
	if (j > 3)
	    return 1;
	return (0);
}


static int	parse_textures_and_color(t_mlx_god* god, char *file_name, int *fd)
{
	char	*str;
	char	flags[6];
	int     spaces;

	*fd = open(file_name, O_RDONLY, 0644);
	ft_memset(god->textures, 0, sizeof(char *) * 4);
	ft_memset(&flags, 0, sizeof(char) * 6);
	str = get_next_line(*fd);
	while (str)
	{
	    spaces = 0;
		if (!ft_strncmp(str, "NO ", 3))
		{
			if (flags[0])
				return (1);
			flags[0] = 1;
			while (str[3 + spaces] == ' ')
			    spaces++;
			god->textures[0] = ft_substr(str, 3 + spaces, ft_strlen(&str[3]) - 1);
		}
		else if (!ft_strncmp(str, "SO ", 3))
		{
			if (flags[1])
				return (1);
			flags[1] = 1;
			while (str[3 + spaces] == ' ')
			    spaces++;
			god->textures[1] = ft_substr(str, 3 + spaces, ft_strlen(&str[3]) - 1);
		}
		else if (!ft_strncmp(str, "WE ", 3))
		{
			if (flags[2])
				return (1);
			flags[2] = 1;
			while (str[3 + spaces] == ' ')
			    spaces++;
			god->textures[2] = ft_substr(str, 3 + spaces, ft_strlen(&str[3]) - 1);
		}
		else if (!ft_strncmp(str, "EA ", 3))
		{
			if (flags[3])
				return (1);
			flags[3] = 1;
			while (str[3 + spaces] == ' ')
			    spaces++;
			god->textures[3] = ft_substr(str, 3 + spaces, ft_strlen(&str[3]) - 1);
		}
		else if (!ft_strncmp(str, "F ", 2))
		{
			if (flags[4])
				return (1);
			flags[4] = 1;
			while (str[2 + spaces] == ' ')
			    spaces++;
			if (parse_color(god, &str[2 + spaces], 0))
			    return (1);
		}
		else if (!ft_strncmp(str, "C ", 2))
		{
			if (flags[5])
				return (1);
			flags[5] = 1;
			while (str[2 + spaces] == ' ')
			    spaces++;
			if (parse_color(god, &str[2 + spaces], 1))
			    return (1);
		}
		else if (ft_strncmp(str, "\n", 1))
			return (1);
		free(str);
		if (flags[0] && flags[1] && flags[2] && flags[3] && flags[4] && flags[5])
		    break;
		str = get_next_line(*fd);
		if (!str)
		    return (1);
	}
	return (0);
}

int room_for_map(t_mlx_god* god, char *file_name)
{
	int		fd;
	int		i = 0;
	int		x_max = 0;
	int		y_max = 0;
	char	*str;

	if (parse_textures_and_color(god, file_name, &fd))
	    return (1);
	str = get_next_line(fd);
	while (str && !ft_strncmp(str, "\n", 1))
	{
		free(str);
		str = get_next_line(fd);
	}
	while (str)
	{
		if (x_max < (int)ft_strlen(str))
			x_max = (int)ft_strlen(str);
		y_max++;
		free(str);
		str = get_next_line(fd);
	}
	god->map = (char **)malloc(sizeof(char *) * y_max + 1);
	while (i < y_max)
	{
		god->map[i] = (char *)malloc(sizeof(char) * (x_max + 1));
		ft_memset(god->map[i], ' ', sizeof(char) * (x_max + 1));
		god->map[i][x_max] = '\0';
		i++;
	}
	god->map[i] = NULL;
	close(fd);
	return (0);
}

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
					god->player->angle = M_PI / 2;
				else if (god->map[i][j] == 'S')
					god->player->angle = 3 * M_PI / 2;
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
					(i == 0 || j == 0 || i == god->size_x || j == god->size_y))
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
	int i;

	i = 0;
	if (room_for_map(god, file_name))
	{
	    printf("error: invalid elements\n");
        return ;
	}
	fill_map(god, file_name);
	if (check_map(god))
	{
		printf("error: sorry but this is shit\n");
		while(god->map[i])
		{
			free(god->map[i]);
			i++;
		}
		free(god->map);
	}
}
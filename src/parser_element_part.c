/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_element_part.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 11:48:31 by ereginia          #+#    #+#             */
/*   Updated: 2022/04/13 16:31:00 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int parse_color(t_mlx_god* god, char *str, char flag)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		buf = ft_itoa(ft_atoi(&str[i]));
		if (ft_atoi(buf) < 0 || ft_atoi(buf) > 255)
		{
			free(buf);
			return (1);
		}
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

static int write_to_textures_massive(t_mlx_god* god, char *flags, int i, char *str)
{
	int sp;

	sp = 0;
	if (*flags)
		return (1);
	*flags = 1;
	while (str[3 + sp] == ' ')
		sp++;
	god->textures[i] = ft_substr(str, 3 + sp, ft_strlen(&str[3 + sp]) - 1);
	return (0);
}

static int get_color(t_mlx_god* god, char *flags, int i, char *str)
{
	int sp;

	sp = 0;	
	if (*flags)
		return (1);
	*flags = 1;
	while (str[2 + sp] == ' ')
		sp++;
	if (parse_color(god, &str[2 + sp], i))
	{
		free(str);
		return (1);
	}
	return (0);
}

int	parse_textures_and_color(t_mlx_god* god, char *file_name, int *fd)
{
	char	*str;
	char	flags[6];
	int		spaces;

	*fd = open(file_name, O_RDONLY, 0644);
	ft_memset(god->textures, 0, sizeof(char *) * 4);
	ft_memset(&flags, 0, sizeof(char) * 6);
	str = get_next_line(*fd);
	if (!str)
		return (1);
	while (str)
	{
		spaces = 0;
		if (!ft_strncmp(str, "NO ", 3))
		{
			if (write_to_textures_massive(god, &flags[0], 0, str))
				return (1);
		}
		else if (!ft_strncmp(str, "SO ", 3))
		{
			if (write_to_textures_massive(god, &flags[1], 1, str))
				return (1);
		}
		else if (!ft_strncmp(str, "WE ", 3))
		{
			if (write_to_textures_massive(god, &flags[2], 2, str))
				return (1);
		}
		else if (!ft_strncmp(str, "EA ", 3))
		{
			if (write_to_textures_massive(god, &flags[3], 3, str))
				return (1);
		}
		else if (!ft_strncmp(str, "F ", 2))
		{
			if (get_color(god, &flags[4], 0, str))
				return (1);
		}
		else if (!ft_strncmp(str, "C ", 2))
		{
			if (get_color(god, &flags[5], 1, str))
				return (1);
		}
		else if (ft_strncmp(str, "\n", 1))
		{
			free(str);
			return (1);
		}
		free(str);
		if (flags[0] && flags[1] && flags[2] && flags[3] && flags[4] && flags[5])
			break;
		str = get_next_line(*fd);
		if (!str)
			return (1);
	}
	return (0);
}
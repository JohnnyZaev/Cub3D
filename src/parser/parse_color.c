/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:49:15 by ereginia          #+#    #+#             */
/*   Updated: 2022/05/04 16:49:18 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	colorize(t_mlx_god *god, int flag, char *buf)
{
	if (flag == 0)
	{
		god->f_color *= 256;
		god->f_color += ft_atoi(buf);
	}
	else
	{
		god->c_color *= 256;
		god->c_color += ft_atoi(buf);
	}
}

static int	loop_body(t_mlx_god *god, char *str, char flag, int *i)
{
	char	*buf;

	buf = ft_itoa(ft_atoi(&str[*i]));
	if (ft_atoi(buf) < 0 || ft_atoi(buf) > 255)
	{
		free(buf);
		return (1);
	}
	while (str[*i] == ' ')
		(*i)++;
	if (ft_strncmp(buf, &str[*i], ft_strlen(buf)))
		return (1);
	colorize(god, flag, buf);
	while (str[*i] == ' ')
		(*i)++;
	(*i) += ft_strlen(buf);
	free(buf);
	return (0);
}

static int	parse_color(t_mlx_god *god, char *str, char flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < 3)
	{
		if (loop_body(god, str, flag, &i))
			return (1);
		while (str[i] == ' ')
			i++;
		if ((str[i] != ',' && j != 2) || (j == 2 && str[i] != '\n'))
			return (1);
		j++;
		i++;
	}
	if (j > 3)
		return (1);
	return (0);
}

int	write_to_textures_massive(t_mlx_god *god, char *flags, int i, char *str)
{
	int	sp;

	sp = 0;
	if (*flags)
		return (1);
	*flags = 1;
	while (str[3 + sp] == ' ')
		sp++;
	god->textures[i] = ft_substr(str, 3 + sp, ft_strlen(&str[3 + sp]) - 1);
	return (0);
}

int	get_color(t_mlx_god *god, char *flags, int i, char *str)
{
	int	sp;

	sp = 0;
	if (*flags)
		return (1);
	*flags = 1;
	while (str[2 + sp] == ' ')
		sp++;
	if (parse_color(god, &str[2 + sp], (char)i))
	{
		free(str);
		return (1);
	}
	return (0);
}

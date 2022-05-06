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

#include "cub3d_bonus.h"

static int	func_choice(char *str)
{
	if (!ft_strncmp(str, "NO ", 3))
		return (0);
	else if (!ft_strncmp(str, "SO ", 3))
		return (1);
	else if (!ft_strncmp(str, "WE ", 3))
		return (2);
	else if (!ft_strncmp(str, "EA ", 3))
		return (3);
	else if (!ft_strncmp(str, "F ", 2))
		return (4);
	else if (!ft_strncmp(str, "C ", 2))
		return (5);
	else if (ft_strncmp(str, "\n", 1))
		return (6);
	return (-1);
}

static int	if_tree(t_mlx_god *god, char *flags, char *str)
{
	int	choice;

	choice = func_choice(str);
	if (choice > -1 && choice < 4)
	{
		if (write_to_textures_massive(god, &flags[choice], choice, str))
			return (1);
	}
	else if (choice > 3 && choice < 6)
	{
		if (get_color(god, &flags[choice], choice - 4, str))
			return (1);
	}
	else if (choice == 6)
	{
		free(str);
		return (1);
	}
	return (0);
}

int	parse_textures_and_color(t_mlx_god *god, char *file_name, int *fd)
{
	char	*str;
	char	flags[6];

	*fd = open(file_name, O_RDONLY, 0644);
	ft_memset(god->textures, 0, sizeof(char *) * 4);
	ft_memset(&flags, 0, sizeof(char) * 6);
	str = get_next_line(*fd);
	if (!str)
		return (1);
	while (true)
	{
		if (if_tree(god, &flags[0], str))
			return (1);
		free(str);
		if (flags[0] && flags[1] && flags[2] && \
			flags[3] && flags[4] && flags[5])
			break ;
		str = get_next_line(*fd);
		if (!str)
			return (1);
	}
	return (0);
}

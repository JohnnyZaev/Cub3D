/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:27:48 by gvarys            #+#    #+#             */
/*   Updated: 2021/12/02 14:53:54 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdupbn(const char *s, int len)
{
	char	*ns;
	int		i;

	ns = (char *)malloc(len + 2);
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\n')
	{
		ns[i] = s[i];
		i++;
	}
	ns[i] = '\n';
	ns[i + 1] = '\0';
	return (ns);
}

static char	*crtstr(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(size);
	if (!str)
		return (NULL);
	while (i != size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

static void	ft_kostylb(char **save, char *buf, int i, int fd)
{
	char	*temp;

	if (i >= 0)
	{
		temp = ft_strdup(save[fd] + (i + 1));
		strdell(&save[fd]);
		save[fd] = temp;
		if (save[fd][0] == '\0')
			strdell(&save[fd]);
		return ;
	}
	else
	{
		if (!save[fd])
			save[fd] = crtstr(1);
		temp = ft_strjoin(save[fd], buf);
		strdell(&save[fd]);
		save[fd] = temp;
		return ;
	}
}

static char	*get_line(char **save, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (save[fd][i] != '\n' && save[fd][i] != '\0')
		i++;
	if (save[fd][i] == '\n' && (save[fd][0] != '\n' || save[fd][1] != '\0'))
	{
		line = ft_strdupbn(save[fd], i);
		ft_kostylb(save, "netb", i, fd);
	}
	else if (save[fd][0] != '\0' && (save[fd][i] == '\0'
			|| save[fd][0] == '\n'))
	{
		line = ft_strdup(save[fd]);
		strdell(&save[fd]);
		if (line[0] == '\0')
			return (NULL);
	}
	else
	{
		strdell(&save[fd]);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save[10243];
	char		buf[BUFFER_SIZE + 1];
	ssize_t		rd;

	if (fd < 0 || fd > 10243 || BUFFER_SIZE < 1)
		return (NULL);
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		buf[rd] = '\0';
		ft_kostylb(save, buf, -1, fd);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (rd < 0)
	{
		strdell(&save[fd]);
		return (NULL);
	}
	return (get_line(save, fd));
}

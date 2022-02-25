/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:03:37 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:54:04 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	splitcounter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*splitalloc(char const *s, char c)
{
	char	*sallc;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	sallc = (char *)malloc(i + 1);
	if (!sallc)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		sallc[i] = s[i];
		i++;
	}
	sallc[i] = '\0';
	return (sallc);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;

	res = (char **)malloc(sizeof(char *) * (splitcounter(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			res[i] = splitalloc(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	res[i] = NULL;
	return (res);
}

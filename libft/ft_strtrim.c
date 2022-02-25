/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:51:26 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:55:11 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cis(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ns;
	size_t	i;
	size_t	start;
	size_t	slen;

	start = 0;
	while (s1[start] != '\0' && cis(s1[start], set))
		start++;
	slen = ft_strlen(s1);
	while (slen > start && cis(s1[slen - 1], set))
		slen--;
	ns = (char *)malloc((slen - start) + 1);
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (start < slen)
		ns[i++] = s1[start++];
	ns[i] = '\0';
	return (ns);
}

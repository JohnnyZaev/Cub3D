/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 10:36:59 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:54:30 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	int		i;
	int		j;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ns = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ns == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j] != '\0')
	{
		ns[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ns[i++] = s2[j++];
	}
	ns[i] = '\0';
	return (ns);
}

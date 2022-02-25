/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:40:36 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:55:01 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t		j;
	char		*buff;

	if (!*little)
		return ((char *)big);
	if (ft_strlen(big) < ft_strlen(little))
		return (NULL);
	while (*big != '\0' && len)
	{
		if (*big == *little)
		{
			buff = (char *)big;
			j = 0;
			while (big[j] == little[j] && len >= ft_strlen(little))
			{
				if (j == ft_strlen(little) - 1)
					return (buff);
				j++;
			}
		}
		len--;
		big++;
	}
	return (NULL);
}

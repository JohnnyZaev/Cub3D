/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:08:37 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:53:17 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned const char	*temp;
	size_t				i;

	temp = str;
	i = 0;
	while (i < n)
	{
		if (temp[i] == (unsigned char)c)
			return ((void *)(temp + i));
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:41:15 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:53:29 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t count)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (s == d || count == 0)
		return (dest);
	if (d > s)
	{
		while (count--)
		{
			d[count] = s[count];
		}
		return (dest);
	}
	while (count > 0)
	{
		*d = *s;
		d++;
		s++;
		count--;
	}
	return (dest);
}

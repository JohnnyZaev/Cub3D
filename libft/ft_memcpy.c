/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:30:23 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:53:26 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	unsigned char	*temp;
	unsigned char	*temp2;

	if (dest == NULL && src == NULL)
		return (NULL);
	temp = (unsigned char *)src;
	temp2 = (unsigned char *)dest;
	while (count--)
	{
		*temp2 = *temp;
		temp++;
		temp2++;
	}
	return (dest);
}

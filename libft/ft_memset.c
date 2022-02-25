/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:40:04 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:53:34 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t count)
{
	unsigned char	*buf;

	buf = destination;
	while (count > 0)
	{
		*buf = c;
		buf++;
		count--;
	}
	return (destination);
}

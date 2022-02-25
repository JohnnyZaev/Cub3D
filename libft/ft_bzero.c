/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:06:50 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:51:42 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *destination, size_t count)
{
	unsigned char	*buf;

	buf = (unsigned char *)destination;
	while (count > 0)
	{
		*buf = '\0';
		buf++;
		count--;
	}
}

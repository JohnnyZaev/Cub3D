/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:46:21 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:54:10 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*temp;

	temp = (char *)str;
	while (*temp != '\0')
	{
		if (*temp == (char)c)
			return (temp);
		temp++;
	}
	if (*temp == (char)c)
		return (temp);
	return (NULL);
}

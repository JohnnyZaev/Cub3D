/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:21:23 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:52:22 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	int	len;

	len = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				len;
	unsigned int	nb;

	len = ft_nlen(n);
	res = (char *)malloc(len + 1);
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	while (nb > 0)
	{
		res[len - 1] = (nb % 10) + 48;
		nb /= 10;
		len--;
	}
	return (res);
}

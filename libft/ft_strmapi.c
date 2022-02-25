/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 10:20:13 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:54:50 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ns;

	if (s == NULL)
		return (NULL);
	ns = (char *)malloc((ft_strlen(s)) + 1);
	if (ns == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ns[i] = f(i, s[i]);
		i++;
	}
	ns[i] = '\0';
	return (ns);
}

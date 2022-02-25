/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:57:49 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:53:00 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*temp;

	res = NULL;
	while (lst != NULL)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (temp == NULL)
		{
			while (res != NULL)
			{
				temp = res->next;
				ft_lstdelone(res, del);
				res = temp;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&res, temp);
		lst = lst->next;
	}
	return (res);
}

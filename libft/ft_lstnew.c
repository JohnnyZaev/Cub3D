/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:59:23 by gvarys            #+#    #+#             */
/*   Updated: 2021/10/15 12:53:08 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlst;

	newlst = (t_list *)malloc(sizeof(*newlst));
	if (newlst == NULL)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}

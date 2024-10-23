/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:42:48 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/25 16:53:00 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*elem;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(NULL);
	if (!new_list)
		return (NULL);
	elem = new_list;
	while (lst)
	{
		elem -> content = (void *)f(lst -> content);
		if (lst -> next)
		{
			elem -> next = ft_lstnew(NULL);
			if (!elem -> next)
			{
				ft_lstclear(&new_list, del);
				return (NULL);
			}
			elem = elem -> next;
		}
		lst = lst -> next;
	}
	return (new_list);
}

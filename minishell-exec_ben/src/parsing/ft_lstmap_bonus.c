/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:12:21 by rmichel-          #+#    #+#             */
/*   Updated: 2024/10/23 18:27:56 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

static t_list	*bl(t_list *l, t_list *s, void *(*f)(void *), void (*r)(void *))
{
	void	*content;
	t_list	*node;

	while (l != NULL)
	{
		content = (*f)(l -> content);
		if (content == NULL)
		{
			r(content);
			ft_lstclear(&s, r);
			return (NULL);
		}
		node = ft_lstnew(content);
		if (node == NULL)
		{
			r(content);
			ft_lstclear(&s, r);
			return (NULL);
		}
		ft_lstadd_back(&s, node);
		l = l -> next;
	}
	return (s);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	void	*content;

	if (lst == NULL)
		return (NULL);
	content = (*f)(lst -> content);
	if (content == NULL)
	{
		del(content);
		return (NULL);
	}
	start = ft_lstnew(content);
	if (start == NULL)
	{
		del(content);
		return (NULL);
	}
	lst = lst -> next;
	return (bl(lst, start, f, del));
}

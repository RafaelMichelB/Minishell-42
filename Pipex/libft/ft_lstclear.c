/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:55:44 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/25 15:22:43 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	if (!lst)
		return ;
	while (*lst)
	{
		elem = *lst;
		*lst = elem -> next;
		del(elem -> content);
		free(elem);
	}
	free(*lst);
}

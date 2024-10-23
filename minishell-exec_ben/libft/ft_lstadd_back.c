/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:37:29 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/25 17:04:30 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (lst && new)
	{
		elem = ft_lstlast(*lst);
		if (!elem)
			*lst = new;
		if (elem)
			elem -> next = new;
		new -> next = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:10:31 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/12 01:10:31 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*copy;

	while (*lst != NULL)
	{
		copy = *lst;
		*lst = (*lst)->next;
		(*del)(copy -> content);
		free(copy);
	}
}

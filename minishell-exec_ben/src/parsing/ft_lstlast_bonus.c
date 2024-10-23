/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 01:17:27 by rmichel-          #+#    #+#             */
/*   Updated: 2024/10/23 18:27:52 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;

	i = ft_lstsize(lst);
	while (i > 1)
	{
		lst = lst -> next;
		i--;
	}
	return (lst);
}

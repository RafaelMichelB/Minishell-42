/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:11:48 by rmichel-          #+#    #+#             */
/*   Updated: 2024/10/23 18:27:47 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pars.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	(*f)(lst -> content);
	ft_lstiter(lst -> next, f);
}

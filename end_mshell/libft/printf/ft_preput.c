/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:10:29 by rmichel-          #+#    #+#             */
/*   Updated: 2023/11/28 16:43:12 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

int	ft_preput(t_list *list, int mv)
{
	t_list	*aux;

	aux = list->next;
	ft_lstdelone(list, &ft_del);
	list = aux;
	return (ft_putlst(aux, mv));
}

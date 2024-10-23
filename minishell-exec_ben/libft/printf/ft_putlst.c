/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:28:01 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/17 17:28:01 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdio.h>

int	ft_putlst(t_list *list, int mv)
{
	int		len;
	t_list	*aux;

	aux = list;
	len = 0;
	while (list != NULL)
	{
		if (list -> content == NULL)
			return (-1);
		if (((char *)(list->content))[0] == mv)
		{
			ft_putchar_fd('\0', 1);
			if (list->next != NULL)
				len++;
		}
		else
		{
			ft_putstr_fd(list->content, 1);
			len += ft_strlen(list -> content);
		}
		list = list->next;
	}
	ft_lstclear(&aux, &ft_del);
	return (len);
}

/*
int	ft_putlst(t_list *list)
{
	t_list	*aux;
	int		len;

	if (list == NULL)
		return (0);
	aux = list -> next;
	len = ft_strlen(list -> content);
	if (((char *)(list->content))[0] == 0)
	{
		ft_putchar_fd('\0', 1);
		ft_lstdelone(list, &ft_del);
		if (aux == NULL)
			return (ft_putlst(aux));
		return (1 + ft_putlst(aux));
	}
	else
	{
		ft_putstr_fd(list -> content, 1);
		ft_lstdelone(list, &ft_del);
		return (len + ft_putlst(aux));
	}
	return (-1);
}
*/
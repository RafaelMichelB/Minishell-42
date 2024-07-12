/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:40:23 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/17 17:40:23 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

static char	*transform_str(char c, int mv)
{
	char	*to_return;

	to_return = ft_calloc(2, sizeof(char));
	if (to_return == NULL)
		return (NULL);
	if (c == '\0')
		to_return[0] = mv;
	else
		to_return[0] = c;
	return (to_return);
}

t_list	*ft_node2(char *sp, va_list arg, unsigned char mv, va_list cpy)
{
	t_list	*list;

	if (sp[0] == 'X')
		return (ft_lstnew(ft_xtoa_caps(va_arg(arg, unsigned int))));
	else if (sp[0] == 'u')
		return (ft_lstnew(ft_utoa(va_arg(arg, unsigned int))));
	else if (sp[0] == 'p' && va_arg(cpy, long long) != 0)
	{
		list = ft_lstnew(ft_strdup("0x"));
		list->next = ft_lstnew(ft_ptoa((va_arg(arg, long long))));
		return (list);
	}
	else if (sp[0] == 'p')
		return (ft_lstnew(ft_ptoa((va_arg(arg, long long)))));
	else if ((unsigned char)(sp[0]) == mv)
		return (ft_lstnew(transform_str('%', mv)));
	else
		return (NULL);
}

t_list	*ft_node(char *sp, va_list arg, unsigned char mv, va_list cpy)
{
	va_copy(cpy, arg);
	if (sp[0] == 'c')
		return (ft_lstnew(transform_str(va_arg(arg, int), mv)));
	else if (sp[0] == 's' && va_arg(arg, char *) == NULL)
		return (ft_lstnew(ft_strdup("(null)")));
	else if (sp[0] == 's')
		return (ft_lstnew(ft_strdup(va_arg(cpy, char *))));
	else if (sp[0] == 'd' || sp[0] == 'i')
		return (ft_lstnew(ft_itoa(va_arg(arg, int))));
	else if (sp[0] == 'x')
		return (ft_lstnew(ft_xtoa(va_arg(arg, unsigned int))));
	else
		return (ft_node2(sp, arg, mv, cpy));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:28:09 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/17 17:28:09 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

static unsigned char	find_max(char *str)
{
	unsigned int	i;
	unsigned char	maxval;

	i = 0;
	maxval = str[i];
	while (str[i] != '\0')
	{
		if (str[i] > maxval)
			maxval = str[i];
		i++;
	}
	return (maxval + 1);
}

static char	*change(char *str, unsigned char maxval)
{
	unsigned int	i;
	char			*new_str;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			new_str[i] = str[i];
			new_str[i + 1] = maxval;
			i++;
		}
		else
			new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

static t_list	*lst_step(char *str, char **s_split, va_list args, int mxvl)
{
	t_list			*list;
	unsigned int	look_conv;
	va_list			cpy;

	look_conv = 0;
	list = ft_lstnew(ft_strdup("Start"));
	if (str[0] != '%')
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(s_split[look_conv])));
		look_conv++;
	}
	while (s_split[look_conv])
	{
		ft_lstadd_back(&list, ft_node(s_split[look_conv], args, mxvl, cpy));
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(&(s_split[look_conv][1]))));
		look_conv++;
	}
	va_end(cpy);
	return (list);
}

int	ft_printf(const char *str, ...)
{
	va_list			args;
	char			**s_split;
	unsigned char	maxval;
	t_list			*list;
	char			*new_str;

	maxval = find_max((char *)str);
	new_str = change((char *)(str), maxval);
	s_split = ft_split(new_str, '%');
	va_start(args, str);
	list = lst_step((char *)(str), s_split, args, maxval);
	if (list == NULL)
		return (0);
	va_end(args);
	ft_free(s_split);
	free(new_str);
	return (ft_preput(list, maxval));
}

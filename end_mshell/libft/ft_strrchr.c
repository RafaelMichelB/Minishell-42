/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:24:40 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/10 04:13:53 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*str_to_return;

	str_to_return = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
		{
			str_to_return = (char *)str;
		}
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return (str_to_return);
}

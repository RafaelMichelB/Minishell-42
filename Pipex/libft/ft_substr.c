/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:43:05 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/24 17:19:41 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	size;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	if (len > 0 && *s != '\0' && start < size)
	{
		if (len > size - start)
		{
			ptr = ft_calloc(sizeof(char), size - start + 1);
			if (ptr != NULL)
				ft_strlcpy(ptr, &s[start], size - start + 1);
		}
		else
		{
			ptr = ft_calloc(sizeof(char), len + 1);
			if (ptr != NULL)
				ft_strlcpy(ptr, &s[start], len + 1);
		}
	}
	else
		ptr = ft_calloc(sizeof(char), 1);
	return (ptr);
}

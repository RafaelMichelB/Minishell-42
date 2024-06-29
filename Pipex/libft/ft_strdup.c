/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:48:05 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/22 15:04:33 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*str;

	if (*s == '\0')
		str = ft_calloc(sizeof(char), 1);
	else
	{
		size = ft_strlen(s) + 1;
		str = (char *)malloc(sizeof(char) * size);
		if (str == NULL)
			return (NULL);
		ft_strlcpy(str, s, size);
	}
	return (str);
}

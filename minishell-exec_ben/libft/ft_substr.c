/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:15:41 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/12 13:48:04 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min_size(size_t size1, size_t size2)
{
	if (size1 > size2)
		return (size2);
	return (size1);
}

size_t	possible_size(size_t len, char const *str)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == '\0')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	nmemb;

	if (start > ft_strlen(s))
	{
		substring = ft_calloc(1, sizeof (char));
		return (substring);
	}
	nmemb = min_size(ft_strlen(s), len);
	nmemb = min_size(possible_size(len, &(s[start])), nmemb);
	substring = ft_calloc(nmemb + 1, sizeof (char));
	if (s == NULL || substring == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
		return (substring);
	substring = ft_memcpy(substring, &s[start], nmemb);
	return (substring);
}

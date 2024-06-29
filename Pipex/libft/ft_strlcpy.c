/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:27:35 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/15 19:58:28 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;
	size_t	i;

	n = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (n);
	if (dstsize <= n)
	{
		while (i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (n);
	}
	while (src[i] != '\0' && (i <= (dstsize - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

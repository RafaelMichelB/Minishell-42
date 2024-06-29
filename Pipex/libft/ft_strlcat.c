/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:28:00 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/15 23:18:58 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (!dst || !src || dstsize <= 0)
		return (j);
	if (dstsize <= i)
		return (dstsize + j);
	if (dstsize > i + j)
		ft_memcpy(dst + i, src, j + 1);
	if (dstsize <= i + j)
	{
		ft_memcpy(dst + i, src, dstsize - i - 1);
		dst[dstsize - 1] = '\0';
	}
	return (i + j);
}

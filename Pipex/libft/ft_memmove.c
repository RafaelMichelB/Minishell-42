/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:48:30 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/15 14:58:42 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (n <= 0)
		return (dst);
	if (dst <= src || dst >= src + n)
		ft_memcpy(d, s, n);
	else
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	return (dst);
}

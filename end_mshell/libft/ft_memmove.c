/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:16:13 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/11 11:40:22 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void *src, size_t size)
{
	long	looked_char;

	if (size == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	looked_char = 0;
	if (dest < src)
	{
		while ((size_t)looked_char < size)
		{
			((char *)dest)[looked_char] = ((char *)src)[looked_char];
			looked_char++;
		}
	}
	else
	{
		looked_char = size - 1;
		while (looked_char >= 0)
		{
			((char *)dest)[looked_char] = ((char *)src)[looked_char];
			looked_char--;
		}
	}
	return (dest);
}

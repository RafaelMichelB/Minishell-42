/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 23:13:03 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/11 11:27:43 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	modif_byte;

	if (!dest && !src)
		return (NULL);
	modif_byte = 0;
	while (modif_byte < n)
	{
		((char *)dest)[modif_byte] = ((char *)src)[modif_byte];
		modif_byte++;
	}
	return (dest);
}

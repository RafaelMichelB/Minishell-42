/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:18:41 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/11 11:43:00 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	looked_dest_char;
	size_t	looked_src_char;
	size_t	original_size;

	original_size = ft_strlen(dest);
	looked_dest_char = ft_strlen(dest);
	looked_src_char = 0;
	if (size <= original_size)
		return (size + ft_strlen((char *)src));
	while (looked_dest_char < size - 1 && src[looked_src_char] != '\0')
	{
		dest[looked_dest_char] = src[looked_src_char];
		looked_dest_char++;
		looked_src_char++;
	}
	dest[looked_dest_char] = '\0';
	return (ft_strlen((char *)src) + original_size);
}

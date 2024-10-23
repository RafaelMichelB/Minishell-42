/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:55:04 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/10 00:56:29 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	looked_char;

	looked_char = 0;
	while (src[looked_char] != '\0' && looked_char < size - 1 && size != 0)
	{
		dest[looked_char] = src[looked_char];
		looked_char++;
	}
	if (size != 0)
		dest[looked_char] = '\0';
	return (ft_strlen(src));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:02:00 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/10 02:34:29 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*to_duplicate;
	size_t	size;

	size = ft_strlen((char *)s);
	to_duplicate = ft_calloc(sizeof (char), size + 1);
	if (to_duplicate == NULL)
		return (NULL);
	ft_memcpy(to_duplicate, s, sizeof (char) * size);
	return (to_duplicate);
}

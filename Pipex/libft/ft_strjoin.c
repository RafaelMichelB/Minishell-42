/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:13:08 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/17 23:00:11 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	size;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size = (ft_strlen(s1) + ft_strlen(s2) + 1);
	ptr = (char *)malloc(sizeof(char) * size);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, size);
	ft_strlcat(ptr, s2, size);
	return (ptr);
}

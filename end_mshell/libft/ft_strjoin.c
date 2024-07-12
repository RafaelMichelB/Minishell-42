/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:20:12 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/16 09:28:32 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(s1);
	size2 = size1 + ft_strlen(s2);
	new_string = ft_calloc(sizeof (char), size2 + 1);
	if (new_string == NULL)
		return (NULL);
	if (size1 > 0)
		ft_strlcat(new_string, s1, size1 + 1);
	if (size2 > 0)
		ft_strlcat(new_string, s2, size2 + 1);
	return (new_string);
}

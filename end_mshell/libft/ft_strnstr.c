/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:35:54 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/10 06:23:39 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	looked_big;
	size_t	looked_small;
	size_t	small_len;

	small_len = ft_strlen(small);
	looked_big = 0;
	if (*small == 0)
		return ((char *)big);
	while (big[looked_big] != '\0' && looked_big < len)
	{
		looked_small = 0;
		while (big[looked_big + looked_small] == small[looked_small] && \
			looked_small + looked_big < len)
		{
			looked_small++;
			if (looked_small == small_len)
				return ((char *)(big + looked_big));
		}
		looked_big++;
	}
	return (NULL);
}

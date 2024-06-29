/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:23:42 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/24 15:57:50 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	if (!len)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while ((i + j < len) && (big[i + j] == little[j]))
			{
				j++;
				if (little[j] == '\0')
					return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	const char *big = "voila ici ce que tu cherches";
	const char *little = "ici";

	printf("%s\n", ft_strnstr(big, little, 10));
	printf("%s\n", ft_strnstr(big, little, 4));
	return (0);
}*/

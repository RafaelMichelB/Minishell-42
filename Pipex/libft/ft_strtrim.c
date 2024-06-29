/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:00:46 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/24 17:13:32 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 == '\0' || *set == '\0')
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end -1]) && end > start)
		end--;
	ptr = ft_substr(s1, start, (end - start));
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	char *str = "voilaiiiiii";
	char c = 'i';

	printf("%s\n", ft_strtrim(str, &c));
	return (0);
}*/

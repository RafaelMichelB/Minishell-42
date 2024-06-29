/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:54:19 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/21 16:54:33 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(s + i));
		else
			i++;
	}
	if ((unsigned char)s[i] == '\0' && (unsigned char)c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char *s = "uasgiofdhb";
	int c = 't' + 256;
	char	*rslt;
	char	*rslt_ft;

	rslt = strchr(s, c);
	rslt_ft = ft_strchr(s, c);
	printf("%s\n", rslt);
	printf("%s\n", rslt_ft);
	return (0);
}*/

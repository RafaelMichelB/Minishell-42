/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 20:51:14 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/20 19:11:52 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			ptr = (char *)(s + i);
		i++;
	}
	if (!(unsigned char)c && ((unsigned char)s[i] == '\0'))
		ptr = (char *)(s + i);
	return (ptr);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char *s = "azero0azer0oee";
	int	d = 'o';
	int	e = '\0';
	int f = 0;
	int	c = 'l';
	int g = 't' + 256;

	printf("on cherche o : %s\n", strrchr(s, d));
	printf("je cherche o : %s\n\n", ft_strrchr(s, d));
	printf("on cherche le vide %s\n", strrchr(s, e));
	printf("je cherche le vide %s\n\n", ft_strrchr(s, e));
	printf("on cherche 0 %s\n", strrchr(s, f));
	printf("je cherche 0 %s\n\n", ft_strrchr(s, f));
	printf("null : %s\n", ft_strrchr(s, c));
	printf("null : %s\n", ft_strrchr(s, g));
	return (0);
}*/

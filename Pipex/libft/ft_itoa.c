/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:01:39 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/24 15:59:12 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_nzero(void)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * 2);
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

static char	*ft_convert(char *ptr, int size, int n)
{
	unsigned int	nb;

	if (ptr == NULL)
		return (NULL);
	if (n < 0)
	{
		nb = (unsigned int)(n * -1);
		ptr[0] = '-';
	}
	else
		nb = (unsigned int)n;
	while (size--)
	{
		if (ptr[0] == '-' && size == 0)
			return (ptr);
		ptr[size] = '0' + (nb % 10);
		nb /= 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				size;
	unsigned int	nb;

	size = 0;
	if (n == 0)
		ptr = ft_nzero();
	else
	{
		if (n > 0)
			nb = (unsigned int)n;
		else
		{
			size++;
			nb = (unsigned int)(n * -1);
		}
		while (nb > 0)
		{
			size++;
			nb /= 10;
		}
		ptr = ft_calloc((size + 1), sizeof(char));
		ft_convert(ptr, size, n);
	}
	return (ptr);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	char	*str;
	char	*str2;
	char	*str3;
	char	*str4;

	str = ft_itoa(0);
	str2 = ft_itoa(-1234);
	str3 = ft_itoa(-2147483648);
	str4 = ft_itoa(12345);
	printf("should be 0 : %s\n", str);
	printf("should be -1234 : %s\n", str2);
	printf("should be -2147483648 : %s\n", str3);
	printf("should be 12345 : %s\n", str4);
	free(str);
	free(str2);
	free(str4);
	return (0);
} */

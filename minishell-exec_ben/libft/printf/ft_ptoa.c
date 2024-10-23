/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:52:15 by rmichel-          #+#    #+#             */
/*   Updated: 2023/11/28 16:43:24 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

static char	*check_special(char *str, int *to_allocate, unsigned long long *n)
{
	free(str);
	if (*n == 0)
		return (ft_strdup("(nil)"));
	if (*n / 2 == 9223372036854775807)
		return (ft_strdup("ffffffffffffffff"));
	if (*n == 9223372036854775807)
		return (ft_strdup("7fffffffffffffff"));
	str = ft_calloc(*to_allocate, sizeof (char));
	return (str);
}

static char	*make_str(char *str, int i, size_t n, size_t divise)
{
	while (divise > 1)
	{
		str[i] = (n / (divise / 16)) + '0';
		if (str[i] > 57)
			str[i] = str[i] - 58 + 'a';
		n = n % (divise / 16);
		divise /= 16;
		i++;
	}
	return (str);
}

char	*ft_ptoa(unsigned long long n)
{
	char				*str;
	int					to_allocate;
	size_t				divise;
	unsigned long long	ncopy;
	int					i;

	if (n == 9223372036854775808U)
		return (ft_strdup("8000000000000000"));
	i = 0;
	ncopy = n;
	divise = 1;
	to_allocate = 1;
	while (ncopy != 0)
	{
		ncopy /= 16;
		divise *= 16;
		to_allocate++;
	}
	str = malloc(0);
	if (str == NULL)
		return (NULL);
	str = check_special(str, &to_allocate, &n);
	if (str == NULL)
		return (NULL);
	return (make_str(str, i, n, divise));
}

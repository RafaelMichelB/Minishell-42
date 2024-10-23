/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xtoa_caps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:28:39 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/17 17:28:39 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

static char	*check_special(int *to_allocate, unsigned int *n)
{
	char	*str;

	if (*n == 0)
		return (ft_strdup("0"));
	str = ft_calloc(*to_allocate, sizeof (char));
	return (str);
}

static char	*make_str(char *str, int i, unsigned int n, size_t divise)
{
	while (divise > 1)
	{
		str[i] = (n / (divise / 16)) + '0';
		if (str[i] > 57)
			str[i] = str[i] - 58 + 'A';
		n = n % (divise / 16);
		divise /= 16;
		i++;
	}
	return (str);
}

char	*ft_xtoa_caps(unsigned int n)
{
	char				*str;
	int					to_allocate;
	size_t				divise;
	unsigned int		ncopy;
	int					i;

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
	str = check_special(&to_allocate, &n);
	if (str == NULL)
		return (NULL);
	return (make_str(str, i, n, divise));
}

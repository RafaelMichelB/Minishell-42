/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:22:00 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/11 23:32:12 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft.h"

static char	*check_special(char *str, int *to_allocate, unsigned int *n, int *i)
{
	free(str);
	(void)i;
	if (*n == 0)
	{
		str = ft_calloc(2, sizeof (char));
		str[0] = '0';
		return (str);
	}
	if (*n == 4294967295)
		return (ft_memcpy(ft_calloc(11, sizeof (char)), "4294967295", 10));
	str = ft_calloc(*to_allocate, sizeof (char));
	return (str);
}

static char	*make_str(char *str, int i, size_t n, size_t divise)
{
	while (divise > 1)
	{
		str[i] = (n / (divise / 10)) + '0';
		n = n % (divise / 10);
		divise /= 10;
		i++;
	}
	return (str);
}

char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				to_allocate;
	size_t			divise;
	unsigned int	ncopy;
	int				i;

	i = 0;
	ncopy = n;
	divise = 1;
	to_allocate = 1;
	while (ncopy != 0)
	{
		ncopy /= 10;
		divise *= 10;
		to_allocate++;
	}
	str = malloc(0);
	if (str == NULL)
		return (NULL);
	str = check_special(str, &to_allocate, &n, &i);
	if (str == NULL)
		return (NULL);
	return (make_str(str, i, n, divise));
}

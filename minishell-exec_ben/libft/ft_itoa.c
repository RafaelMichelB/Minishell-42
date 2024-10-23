/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:22:00 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/16 09:55:10 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_special(char *str, int *to_allocate, int *n, int *i)
{
	int	ncopy;

	free(str);
	ncopy = *n;
	if (*n == 0)
	{
		str = ft_calloc(2, sizeof (char));
		if (str == NULL)
			return (NULL);
		str[0] = '0';
		return (str);
	}
	if (*n == 2147483647)
		return (ft_strdup("2147483647"));
	if (*n < 0)
	{
		(*n) = (*n) * (-1);
		(*i)++;
		str = ft_calloc(*to_allocate + 1, sizeof (char));
	}
	else
		str = ft_calloc(*to_allocate, sizeof (char));
	if (ncopy < 0 && str != NULL)
		str[0] = '-';
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

char	*ft_itoa(int n)
{
	char	*str;
	int		to_allocate;
	size_t	divise;
	int		ncopy;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
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

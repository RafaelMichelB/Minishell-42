/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:43:47 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/16 19:44:02 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *ptr)
{
	int	i;
	int	isneg;
	int	num;

	num = 0;
	isneg = 1;
	i = 0;
	if (ptr[i] != '\0')
	{
		while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == ' ')
			i++;
		if (ptr[i] == 45 || ptr[i] == 43)
		{
			if (ptr[i] == 45)
				isneg *= -1;
			i++;
		}
		while (ft_isdigit(ptr[i]))
		{
			num = (num * 10 + (ptr[i] - 48));
			i++;
		}
	}
	num *= isneg;
	return (num);
}

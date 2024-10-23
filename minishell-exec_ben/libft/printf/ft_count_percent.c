/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:38:33 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/17 17:38:33 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"

unsigned int	ft_count_percent(char *str)
{
	unsigned int	i;
	unsigned int	nb_percent;

	i = 0;
	nb_percent = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			nb_percent++;
			i++;
		}
		else if (str[i] == '%')
			nb_percent++;
		i++;
	}
	return (nb_percent);
}

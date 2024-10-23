/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:13 by rmichel-          #+#    #+#             */
/*   Updated: 2024/07/13 10:51:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi2(const char *nbr)
{
	int	nbr_to_return;
	int	looked_char;
	int	sign;

	sign = 1;
	looked_char = 0;
	nbr_to_return = 0;
	while ((nbr[looked_char] >= 9 && nbr[looked_char] <= 13) || \
			nbr[looked_char] == 32 || nbr[looked_char] == '"')
		looked_char++;
	if (nbr[looked_char] == '-')
		sign *= -1;
	if (nbr[looked_char] == '+' || nbr[looked_char] == '-')
		looked_char++;
	while (ft_isdigit(nbr[looked_char]) || nbr[looked_char] == '"')
	{
		if (nbr[looked_char] != '"')
			nbr_to_return = 10 * nbr_to_return + (nbr[looked_char] - 48);
		looked_char++;
	}
	return (nbr_to_return * sign);
}

int	ft_atoi(const char *nbr)
{
	int	nbr_to_return;
	int	looked_char;
	int	sign;

	sign = 1;
	looked_char = 0;
	nbr_to_return = 0;
	while ((nbr[looked_char] >= 9 && nbr[looked_char] <= 13) || \
			nbr[looked_char] == 32)
		looked_char++;
	if (nbr[looked_char] == '-')
		sign *= -1;
	if (nbr[looked_char] == '+' || nbr[looked_char] == '-')
		looked_char++;
	while (ft_isdigit(nbr[looked_char]))
	{
		nbr_to_return = 10 * nbr_to_return + (nbr[looked_char] - 48);
		looked_char++;
	}
	return (nbr_to_return * sign);
}

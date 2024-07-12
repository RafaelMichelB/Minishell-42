/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:31:34 by dbonali           #+#    #+#             */
/*   Updated: 2024/02/12 18:36:37 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrft(int nbr)
{
	int	i;

	i = 0;
	if (nbr < 0)
	{
		if (nbr == -2147483648)
		{
			write(1, "-2147483648", 11);
			return (11);
		}
		write(1, "-", 1);
		i += 1;
		nbr = (unsigned int)(nbr * -1);
	}
	else
		nbr = (unsigned int)nbr;
	if (nbr >= 10)
	{
		i += ft_putnbrft(nbr / 10);
		i += ft_putnbrft(nbr % 10);
	}
	else
		i += ft_putcharft(nbr + '0');
	return (i);
}

int	ft_putbase(unsigned int nbr, int format)
{
	int	count;

	count = 0;
	if (nbr >= 16)
	{
		count += ft_putbase(nbr / 16, format);
		count += ft_putbase(nbr % 16, format);
	}
	else if (nbr == 0 || format == 2)
		count += ft_putcharft("0123456789ABCDEF"[nbr]);
	else
		count += ft_putcharft("0123456789abcdef"[nbr]);
	return (count);
}

int	ft_putptr(unsigned long long nbr)
{
	int	i;

	i = 0;
	if (nbr >= 16)
	{
		i += ft_putptr(nbr / 16);
		i += ft_putptr(nbr % 16);
	}
	else
	{
		if (nbr < 10)
			i += ft_putcharft(nbr + '0');
		else
			i += ft_putcharft(nbr + 'a' - 10);
	}
	return (i);
}

int	ft_putunbr(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr >= 10)
	{
		i += ft_putunbr(nbr / 10);
		i += ft_putunbr(nbr % 10);
	}
	else
		i += ft_putcharft(nbr + '0');
	return (i);
}

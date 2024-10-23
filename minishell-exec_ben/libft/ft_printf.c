/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:31:46 by dbonali           #+#    #+#             */
/*   Updated: 2024/02/12 18:35:48 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args_lst;
	int		i;
	int		count;

	va_start(args_lst, str);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += ft_format(str[i + 1], args_lst);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
			count++;
		}
	}
	return (count);
}

int	ft_format(const char c, va_list args_lst)
{
	if (c == 'c')
		return (ft_putcharft(va_arg(args_lst, int)));
	if (c == 's')
		return (ft_putstrft(va_arg(args_lst, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbrft(va_arg(args_lst, int)));
	if (c == 'x' || c == 'X')
		return (ft_format2(c, args_lst, 1));
	if (c == 'u')
		return (ft_putunbr(va_arg(args_lst, unsigned int)));
	if (c == 'p')
		return (ft_format2(c, args_lst, 2));
	if (c == '%')
		return (ft_putcharft('%'));
	return (0);
}

int	ft_putcharft(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstrft(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		i += 6;
		return (i);
	}
	while (str[i])
	{
		ft_putcharft(str[i]);
		i++;
	}
	return (i);
}

int	ft_format2(const char c, va_list args_lst, int format)
{
	unsigned long long	temp;

	if (format == 1)
	{
		if (c == 'x')
			return (ft_putbase(va_arg(args_lst, unsigned int), 1));
		else
			return (ft_putbase(va_arg(args_lst, unsigned int), 2));
	}
	else
	{
		temp = (va_arg(args_lst, unsigned long long));
		if (!temp)
		{
			write(1, "(nil)", 5);
			return (5);
		}
		else
		{
			write(1, "0x", 2);
			return (ft_putptr(temp) + 2);
		}
	}
}

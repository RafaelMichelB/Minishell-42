/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:03:33 by dbonali           #+#    #+#             */
/*   Updated: 2024/02/12 18:35:47 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

int	ft_printf(const char *s, ...);
int	ft_format(const char c, va_list args_lst);
int	ft_format2(const char c, va_list args_lst, int format);
int	ft_putcharft(char c);
int	ft_putstrft(char *str);
int	ft_putnbrft(int nbr);
int	ft_putbase(unsigned int nbr, int format);
int	ft_putptr(unsigned long long nbr);
int	ft_putunbr(unsigned int nbr);

#endif

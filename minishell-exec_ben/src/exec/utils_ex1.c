/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ex1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:09:28 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/23 20:20:48 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_dec(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n / 10 != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*temp;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_dec(n);
	temp = malloc((sizeof (char)) * (len) + 1);
	if (temp == NULL)
		return (NULL);
	temp[len] = '\0';
	len--;
	if (n < 0)
	{
		temp[0] = '-';
		n *= -1;
	}
	if (n == 0)
		return (free(temp), ft_strdup("0"));
	while (len >= 0 && n > 0)
	{
		temp[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (temp);
}

char	*joinspace(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*dup;

	i = 0;
	j = 0;
	dup = (char *)malloc((sizeof (char)) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	while (s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = ' ';
	i++;
	while (s2[j] != '\0')
	{
		dup[i] = s2[j];
		i++;
		j++;
	}
	dup[i] = '\0';
	return (dup);
}

int	ft_atoi(char *ptr)
{
	int			i;
	long long	result;
	int			sign;

	i = 0;
	result = 0;
	sign = 1;
	while ((ptr[i] >= 9 && ptr[i] <= 13) || ptr[i] == 32)
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (ptr[i] != '\0' && (ptr[i] >= 48 && ptr[i] <= 57))
	{
		result = result * 10 + (ptr[i] - '0');
		i++;
	}
	return (result * sign);
}

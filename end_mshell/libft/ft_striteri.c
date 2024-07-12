/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:52:12 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/09 20:31:25 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	looked_char;

	looked_char = 0;
	while (s[looked_char] != '\0')
	{
		f(looked_char, &s[looked_char]);
		looked_char++;
	}
}

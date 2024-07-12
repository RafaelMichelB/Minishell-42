/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:18:23 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/09 20:31:25 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str2;
	unsigned int	looked_char;

	looked_char = 0;
	str2 = malloc((ft_strlen(s) + 1) * sizeof (char));
	if (str2 == NULL)
		return (NULL);
	while (s[looked_char] != '\0')
	{
		str2[looked_char] = f(looked_char, s[looked_char]);
		looked_char++;
	}
	str2[looked_char] = '\0';
	return (str2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:34:56 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/11 23:20:41 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	look_ch;

	look_ch = 0;
	if (n == 0)
		return (0);
	while ((s1[look_ch] != '\0' || s2[look_ch] != '\0') && \
			look_ch < n - 1)
	{
		if ((unsigned char)(s1[look_ch]) != (unsigned char)(s2[look_ch]))
			return ((unsigned char)s1[look_ch] - (unsigned char)s2[look_ch]);
		look_ch++;
	}
	return ((unsigned char)s1[look_ch] - (unsigned char)s2[look_ch]);
}

/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	look_ch;

	look_ch = 0;
	if (n == 0)
		return (0);
	while (s1[look_ch] != '\0' && s2[look_ch] != '\0' && \
			look_ch < n - 1)
	{
		if ((int)(s1[look_ch]) != (int)(s2[look_ch]))
			return (s1[look_ch] - s2[look_ch]);
		look_ch++;
	}
	return ((unsigned char)s1[look_ch] - (unsigned char)s2[look_ch]);
}
*/

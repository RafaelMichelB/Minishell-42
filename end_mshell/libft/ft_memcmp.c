/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 22:37:27 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/10 01:18:43 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	size_t	look_b;

	look_b = 0;
	if (n == 0)
		return (0);
	while (((unsigned char *)p1)[look_b] == ((unsigned char *)p2)[look_b] && \
			look_b < n - 1)
		look_b++;
	return (((unsigned char *)p1)[look_b] - ((unsigned char *)p2)[look_b]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:39:38 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/13 10:08:27 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*to_allocate;

	if (nmemb * size == 0)
		return (malloc(0));
	if ((nmemb * size) / size != nmemb)
		return (NULL);
	to_allocate = malloc(nmemb * size);
	if (to_allocate == NULL)
		return (NULL);
	ft_bzero(to_allocate, nmemb * size);
	return (to_allocate);
}

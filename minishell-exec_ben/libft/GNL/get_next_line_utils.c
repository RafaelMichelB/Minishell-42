/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 23:41:36 by rmichel-          #+#    #+#             */
/*   Updated: 2023/11/29 15:40:09 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_special(int *pos, char **buffer)
{
	char	*str;
	char	*temp;

	if (!(*buffer))
		return (ft_callocg(1));
	while ((*buffer)[*pos] != '\n' && (*buffer)[*pos] != '\0')
		(*pos)++;
	if ((*buffer)[*pos] == '\n')
	{
		temp = ft_strdupg(*buffer);
		free(*buffer);
		*buffer = ft_strdupg(&(temp[*pos + 1]));
		if (*pos != 0)
		{
			str = ft_memcpyg(ft_callocg(*pos + 2), temp, *pos);
			str[*pos] = '\n';
		}
		else
			str = ft_memcpyg(ft_callocg(*pos + 2), temp, *pos + 1);
		free(temp);
		return (str);
	}
	str = ft_memcpyg(ft_callocg(*pos + 1), *buffer, *pos);
	return (str);
}

void	*ft_callocg(size_t nmemb)
{
	char	*to_allocate;
	size_t	i;

	i = 0;
	to_allocate = malloc(nmemb * sizeof(char));
	if (to_allocate == NULL)
		return (NULL);
	while (i < nmemb)
	{
		to_allocate[i] = 0;
		i++;
	}
	return (to_allocate);
}

char	*ft_strdupg(const char *s)
{
	char	*to_duplicate;
	size_t	size;
	size_t	actual;

	actual = 0;
	size = 0;
	while (s[size] != '\0')
		size++;
	to_duplicate = ft_callocg(size + 1);
	if (to_duplicate == NULL)
		return (NULL);
	while (actual < size)
	{
		to_duplicate[actual] = s[actual];
		actual++;
	}
	return (to_duplicate);
}

void	*ft_memcpyg(void *dest, const void *src, size_t n)
{
	size_t	modif_byte;

	if (!dest && !src)
		return (NULL);
	modif_byte = 0;
	while (modif_byte < n)
	{
		((char *)dest)[modif_byte] = ((char *)src)[modif_byte];
		modif_byte++;
	}
	return (dest);
}

char	*add_buffer(char *line, char **buff, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] != 0)
		i++;
	str = ft_callocg((i + len + 2));
	i = 0;
	while (line[i] != 0)
	{
		str[i] = line[i];
		i++;
	}
	j = -1;
	while (++j < len)
		str[i + j] = (*buff)[j];
	free(line);
	if (len != BUFFER_SIZE)
		str[i + j] = '\n';
	i = -1;
	while (++i < BUFFER_SIZE)
		(*buff)[i] = 0;
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:52:17 by rmichel-          #+#    #+#             */
/*   Updated: 2023/11/29 16:52:19 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strncmpg(const char *s1, const char *s2, size_t n)
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

char	*free_l(char *line, char **bf)
{
	if ((*bf)[0] == '\0')
	{
		free(*bf);
		*bf = NULL;
	}
	return (line);
}

char	*gnl2(int fd, char *buff_temp, char *line, char **buffer)
{
	int	i;

	i = 0;
	while (buff_temp[i] != '\n' && buff_temp[i] != '\0')
		i++;
	if (buff_temp[i] == '\n')
	{
		free(*buffer);
		*buffer = ft_strdupg(&(buff_temp[i + 1]));
		line = add_buffer(line, &buff_temp, i);
		free(buff_temp);
		return (line);
	}
	line = add_buffer(line, &buff_temp, BUFFER_SIZE);
	i = read(fd, buff_temp, BUFFER_SIZE);
	if (i == -1)
		return (NULL);
	if (i == 0)
	{
		free(*buffer);
		*buffer = NULL;
		free(buff_temp);
		return (line);
	}
	return (gnl2(fd, buff_temp, line, buffer));
}

char	*get_next_line(int fd)
{
	static char	*bf = NULL;
	char		*line;
	char		*buff_temp;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = check_special(&i, &bf);
	if (line == NULL || line[i] == '\n')
		return (free_l(line, &bf));
	buff_temp = ft_callocg(BUFFER_SIZE + 1);
	i = read(fd, buff_temp, BUFFER_SIZE);
	if (i == -1 || (i == 0 && line[0] == '\0'))
	{
		free(bf);
		bf = NULL;
		free(line);
		free(buff_temp);
		return (NULL);
	}
	if (bf && ft_strncmp(bf, line, BUFFER_SIZE) != 0)
		return (free_l(line, &buff_temp));
	return (gnl2(fd, buff_temp, line, &bf));
}

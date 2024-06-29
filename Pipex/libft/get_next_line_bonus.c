/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:00:48 by dbonali           #+#    #+#             */
/*   Updated: 2024/03/21 23:03:16 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	line = NULL;
	if (!stash[fd])
		stash[fd] = NULL;
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	line = extract_line(stash[fd], line);
	stash[fd] = clean_stash(stash[fd]);
	if (!line[0])
		return (free(line), NULL);
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buff;
	int		readed;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	readed = BUFFER_SIZE;
	while (!found_new_line(stash))
	{
		readed = (int)read(fd, buff, BUFFER_SIZE);
		if (readed <= 0)
		{
			if (readed < 0)
				return (free(stash), free(buff), NULL);
			free(buff);
			return (stash);
		}
		buff[readed] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	free(buff);
	return (stash);
}

char	*extract_line(char *stash, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
	{
		line = (char *)malloc(sizeof(char) * (i + 2));
		if (line != NULL)
		{
			j = 0;
			while (j <= i)
			{
				line[j] = stash[j];
				j++;
			}
			line[j] = '\0';
		}
	}
	else
		line = ft_strdup(stash);
	return (line);
}

char	*clean_stash(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	else
	{
		temp = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i));
		if (temp == NULL)
			return (NULL);
		j = 0;
		while (j < (ft_strlen(stash) - i - 1))
		{
			temp[j] = stash[i + j + 1];
			j++;
		}
		temp[j] = '\0';
		free(stash);
	}
	return (temp);
}

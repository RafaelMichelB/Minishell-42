/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:04:21 by dbonali           #+#    #+#             */
/*   Updated: 2024/03/21 22:58:37 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash)
		{
			free(stash);
			stash = NULL;
		}
		return (NULL);
	}
	line = NULL;
	if (!stash)
		stash = NULL;
	stash = read_and_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = extract_line(stash, line);
	stash = clean_stash(stash);
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
		stash = ft_strjoingnl(stash, buff);
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
		line = ft_strdupgnl(stash);
	return (line);
}

char	*clean_stash(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0' || (stash[i] == '\n' && stash[i + 1] == '\0'))
		return (free(stash), NULL);
	else if (stash[i] == '\n')
	{
		temp = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i));
		if (temp == NULL)
			return (NULL);
		j = 0;
		while (j < (ft_strlengnl(stash) - i - 1))
		{
			temp[j] = stash[i + j + 1];
			j++;
		}
		temp[j] = '\0';
		free(stash);
		stash = temp;
	}
	return (stash);
}

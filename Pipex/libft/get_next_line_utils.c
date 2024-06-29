/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:26:10 by dbonali           #+#    #+#             */
/*   Updated: 2024/03/21 23:05:49 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_new_line(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoingnl(char *stash, char *buff)
{
	char	*temp;

	if (stash != NULL)
	{
		temp = (char *)malloc(sizeof(char)
				* (ft_strlengnl(stash) + ft_strlengnl(buff) + 1));
		if (temp == NULL || (ft_strlengnl(stash) + ft_strlengnl(buff)
				+ 1) > 20024)
		{
			if (temp)
				free(temp);
			free(stash);
			return (NULL);
		}
		temp = ft_strcpycat(temp, stash, buff);
		free(stash);
		return (temp);
	}
	return (ft_strdupgnl(buff));
}

char	*ft_strdupgnl(char *str)
{
	char	*buff;
	int		i;

	buff = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlengnl(str))
	{
		buff[i] = str[i];
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

char	*ft_strcpycat(char *stash, char *temp, char *buff)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlengnl(temp);
	while (i < len)
	{
		stash[i] = temp[i];
		i++;
	}
	while (buff[j] != '\0')
	{
		stash[i + j] = buff[j];
		j++;
	}
	stash[i + j] = '\0';
	return (stash);
}

int	ft_strlengnl(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

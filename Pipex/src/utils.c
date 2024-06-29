/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:09:05 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/17 21:50:31 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	ft_exit(int i)
{
	if (i == 4)
	{
		write(2, "Error cmd not found\n", 20);
		exit(1);
	}
	if (i == 1 || i == 3)
		errno = EINVAL;
	if (i == 2)
		errno = ENOENT;
	if (errno != 0)
		perror("💀 \033[1;31mError\033[0m ");
	exit(1);
}

char	**get_paths(char **envp)
{
	char	*path;
	char	**cmd_path;
	char	*look4;
	int		i;
	int		j;

	i = -1;
	look4 = "PATH=";
	while (envp[++i])
	{
		j = 0;
		while (envp[i][j] == look4[j])
		{
			j++;
			if (!look4[j])
			{
				path = ft_substr(envp[i], 5,
						(ft_strlen(envp[i]) - 5));
				cmd_path = ft_split(path, ':');
				return (free(path), cmd_path);
			}
		}
	}
	return (NULL);
}

char	*get_full_path(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	if (!full_path)
		return (free(tmp), NULL);
	free(tmp);
	return (full_path);
}

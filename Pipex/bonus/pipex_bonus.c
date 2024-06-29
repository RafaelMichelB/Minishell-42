/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:11:06 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/17 21:11:08 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	check_last_arg(char *argv, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*full_path;
	int		i;

	cmd = ft_split(argv, ' ');
	paths = get_paths(envp);
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		full_path = get_full_path(paths[i], cmd[0]);
		if (access(full_path, X_OK) != -1)
		{
			free(full_path);
			ft_free(paths);
			ft_free(cmd);
			return (0);
		}
		free(full_path);
	}
	ft_free(cmd);
	ft_free(paths);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:52 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:50:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_del(void	*content)
{
	free(content);
}

char	**find_all_path(char **var_env)
{
	int		i;
	char	**t1;
	char	**t2;

	i = 0;
	while (var_env[i] != NULL)
	{
		if (ft_strncmp("PATH", var_env[i], 4) == 0)
		{
			t1 = ft_split(var_env[i], '=');
			t2 = ft_split(t1[1], ':');
			ft_free(t1);
			return (t2);
		}
		i++;
	}
	return (NULL);
}

char	*find_nice_path(char *cmd, char **env)
{
	char	**split_cmd;
	char	*poss_path1;
	char	*poss_path2;
	int		i;
	char	**path;

	path = find_all_path(env);
	if (path == NULL)
		return (NULL);
	i = -1;
	split_cmd = ft_split(cmd, ' ');
	while (path[++i] != NULL)
	{
		poss_path1 = ft_strjoin(path[i], "/");
		if (split_cmd[0] == NULL)
			poss_path2 = ft_strjoin(poss_path1, "noexist");
		else
			poss_path2 = ft_strjoin(poss_path1, split_cmd[0]);
		if (access(poss_path2, F_OK) == 0)
			return (ft_free(split_cmd), free(poss_path1), \
			ft_free(path), poss_path2);
		free(poss_path1);
		free(poss_path2);
	}
	return (ft_free(split_cmd), ft_free(path), NULL);
}

int	only_in(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}

int	only_in2(char *str, char c, char c2)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c && str[i] != c2)
			return (0);
	}
	return (1);
}

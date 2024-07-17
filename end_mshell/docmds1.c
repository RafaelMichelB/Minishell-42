/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   docmds1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:25 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:49:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	do1cmd2(int fd[], int *i, t_cmd *cmds, char **env)
{
	if (fd[1] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[*i].path, 2), \
		ft_putendl_fd(": Permission denied", 2), ft_free(env), exit(1));
	if (fd[1] != -1)
		close(fd[1]);
	if (cmds[*i].type == RED_OUT)
		fd[1] = open(cmds[*i].path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd[1] = open(cmds[*i].path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	(*i)++;
}

void	do1cmd3(int fd[], int *i, t_cmd *cmds[], char **env)
{
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), \
		ft_putstr_fd(cmds[0][*i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), clear_cmds(cmds[1]), \
		free(cmds[0]), ft_free(env), exit(1));
	if (fd[0] != -1)
		close(fd[0]);
	fd[0] = open(cmds[0][*i].path, O_RDONLY);
	(*i)++;
}

int	do1cmd41(t_cmd *cmds, t_cmd *cmd, int i, char **env)
{
	int j;

	j = i;
	while (access(cmds[j].path, F_OK) == 0 || cmds[j].type == BUILTIN)
		j++;
	return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[j].path, 2), \
		ft_putendl_fd(": command not found", 2), clear_cmds(cmds), \
		free(cmd), ft_free(env), exit(127), 1);
}

int	do1cmd42(t_cmd *cmds, t_cmd *cmd, int i, char **env)
{
	if (access(cmds[i - 1].path, F_OK) == 0 && \
	access(cmds[i - 1].path, W_OK) != 0)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[i - 1].path, 2), \
ft_putendl_fd(": Permission denied", 2), clear_cmds(cmd), free(cmds), \
ft_free(env), exit(1), 0);
	return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), \
		free(cmds), clear_cmds(cmd), ft_free(env), exit(1), 0);
}

int	do1cmd43(t_cmd *cmds, t_cmd *cmd, int i, char **env)
{
	return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[i - 2].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), \
		free(cmds), clear_cmds(cmd), ft_free(env), exit(1), 0);
}

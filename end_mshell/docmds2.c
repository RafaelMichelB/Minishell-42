/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   docmds2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:49:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	do1cmd44(t_cmd *cmds, t_cmd *cmd, int j, char **env)
{
	if (access(cmd[j].path, X_OK) != 0)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[j].path, 2), \
		ft_putstr_fd(": Permission denied\n", 2), free(cmds), clear_cmds(cmd), \
		ft_free(env), exit(126), 0);
	return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[j].path, 2), \
		ft_putstr_fd(": Is a directory\n", 2), free(cmds), clear_cmds(cmd), \
		ft_free(env), exit(126), 0);
}

int	do1cmd45(t_cmd *cmds, t_cmd *cmd, int j, char **env)
{
	return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[j].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), \
		free(cmds), clear_cmds(cmd), ft_free(env), exit(127), 0);
}

void	do1cmd32(int fd[], int *i, t_cmd *cmds[], char **env)
{
	fd[0] = open("/dev/stdin", O_RDONLY);
	while (cmds[0][*i].type == RED_IN)
		do1cmd3(fd, i, cmds, env);
}

int	do1cmd5(t_cmd *cmd, t_cmd *cmds, char **env, int fd[])
{
	return (clear_cmds(cmd), free(cmds), ft_free(env), \
	close(fd[0]), exit(0), 1);
}

int	do1cmd(t_cmd *cmds, char **env, t_cmd *cmd, int i)
{
	int		fd[3];
	t_cmd	*c[2];

	c[0] = cmds;
	c[1] = cmd;
	dc(fd, &i, c, env);
	fd[2] = i++;
	if (cmds[i - 1].type == NONE)
		docmdb(c, i, env, fd);
	if (access(cmds[fd[2]].path, F_OK) != 0)
		return (do1cmd45(cmds, cmd, fd[2], env));
	if (fd[0] == -1)
		return (do1cmd43(cmds, cmd, i, env), 1);
	dup2(fd[0], 0);
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmds[i].type != END)
		do1cmd2(fd, &i, cmds, env);
	if (fd[1] == -1)
		return (close(fd[0]), do1cmd42(cmds, cmd, i, env), 2);
	dup2(fd[1], 1);
	close_fds(fd);
	if (execve(cmds[fd[2]].path, cmds[fd[2]].args, env))
		return (do1cmd44(cmds, cmd, fd[2], env), 1);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:33 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/19 14:10:26 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	ft_exec(char *arg, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*full_path;
	int		i;

	cmd = ft_split(arg, ' ');
	paths = get_paths(envp);
	i = 0;
	while (paths[i] != NULL)
	{
		full_path = get_full_path(paths[i], cmd[0]);
		execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
	ft_free(paths);
	ft_free(cmd);
	return (-1);
}

void	child_process(char **argv, int *p_fd, char **envp)
{
	int	file;

	if (access(argv[1], F_OK | R_OK) == -1)
		ft_exit(-1);
	file = open(argv[1], O_RDONLY);
	dup2(file, 0);
	close(file);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	close(p_fd[1]);
	if (ft_exec(argv[2], envp))
	{
		write(2, "Error cmd not found\n", 20);
		exit(1);
	}
	exit(1);
}

void	parent_process(char **argv, int *p_fd, char **envp)
{
	int		fd;
	int		status;

	while (waitpid(-1, &status, 0) > 0)
	{
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
	fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	dup2(fd, 1);
	close(fd);
	if (ft_exec(argv[3], envp) < 0)
	{
		write(2, "Error cmd not found\n", 20);
		exit(1);
	}
}
/* if (WIFEXITED(status))
		{
			if (WIFEXITED(status) != 1)
				exit(1);
		}*/

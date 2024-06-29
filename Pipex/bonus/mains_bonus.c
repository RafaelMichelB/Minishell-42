/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mains_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:16:05 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/17 21:48:34 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	do_pipe(char *arg, char **envp)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
		ft_exit(-1);
	pid = fork();
	if (pid == -1)
		ft_exit(-1);
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		if (ft_exec(arg, envp) < 0)
			ft_exit(4);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && WIFEXITED(status) != 1)
			exit(1);
	}
}

int	pipex_main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd_in;
	int		fd_out;

	i = 2;
	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in, 0);
	close(fd_in);
	while (i < (argc - 2))
		do_pipe(argv[i++], envp);
	fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd_out, 1);
	close(fd_out);
	if (ft_exec(argv[argc - 2], envp) < 0)
		ft_exit(4);
	return (1);
}

int	no_file2_main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd_in;

	i = 2;
	fd_in = open(argv[1], O_RDONLY);
	dup2(fd_in, 0);
	close(fd_in);
	while (i < (argc - 1))
		do_pipe(argv[i++], envp);
	if (ft_exec(argv[argc - 1], envp) < 0)
		ft_exit(4);
	return (1);
}

void	hdoc_input(char **argv, int *p_fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		write(1, "here_doc> ", 10);
		line = get_next_line(0);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0
			&& line[ft_strlen(argv[2])] == '\n')
			break ;
		ft_putstr_fd(line, p_fd[1]);
		free(line);
	}
	close(p_fd[1]);
	dup2(p_fd[0], 0);
	close(p_fd[0]);
}

int	hdoc_main(int last, int argc, char **argv, char **envp)
{
	int		i;
	int		fd_out;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		ft_exit(-1);
	hdoc_input(argv, p_fd);
	i = 3;
	while (i < (argc - 1 - last))
		do_pipe(argv[i++], envp);
	if (last == 1)
	{
		fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd_out, 1);
		close(fd_out);
	}
	if (ft_exec(argv[argc - (1 + last)], envp) < 0)
		ft_exit(4);
	return (1);
}

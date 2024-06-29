/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:07:01 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/19 14:10:39 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		ft_exit(1);
	if (pipe(fd) == -1)
		ft_exit(-1);
	pid = fork();
	if (pid == -1)
		ft_exit(-1);
	if (!pid)
		child_process(argv, fd, envp);
	parent_process(argv, fd, envp);
	return (0);
}

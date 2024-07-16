/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:48:09 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:48:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	escape_print(char c, int fd)
{
	ft_putstr_fd("\\", fd);
	ft_putchar_fd(c, fd);
}

void	print_arg(char *arg, int fd)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			escape_print(arg[i], fd);
		}
		else
			ft_putchar_fd(arg[i], fd);
		i++;
	}
}

int	only_n(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	bltin_echo(t_cmd cmd, int fd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (only_n(cmd.args[1]))
	{
		if (count_size_args(cmd.args) <= 2)
			return ;
		new_line = 0;
		i = 2;
	}
	while (i++ < count_size_args(cmd.args))
	{
		if (only_n(cmd.args[i - 1]) == 1)
			i = i;
		else
		{
			print_arg(cmd.args[i - 1], fd);
			if (i < count_size_args(cmd.args))
				ft_putstr_fd(" ", fd);
		}
	}
	if (new_line == 1)
		ft_putstr_fd("\n", fd);
}

int	builtin_echo_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	j;
	int	fd[2];

	i = -1;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[++i].type == RED_IN)
	{
		if (fd[0] == -1)
			return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), ft_putendl_fd(NOF, 2), 1);
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
	}
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd[i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), 1);
	j = i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2b(fd, &i, cmd, env);
	if (fd[1] == -1)
	{
		if (access(cmd[i - 1].path, F_OK) == 0 && access(cmd[i - 1].path, W_OK) != 0)
			return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), \
ft_putendl_fd(": Permission denied", 2), env_clear(env), close(fd[0]), 1);
		return (close(fd[0]), 1);
	}
	if (count_size_args(cmd[j].args) == 1)
		return (ft_putstr_fd("\n", fd[1]), close_fds(fd), 0);
	return (bltin_echo(cmd[j], fd[1]), close_fds(fd), 0);
}

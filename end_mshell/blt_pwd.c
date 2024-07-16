/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:48:46 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:48:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	bltin_pwd(int fd)
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = calloc(size, sizeof(char *));
	if (!buffer)
		return (1);
	while (getcwd(buffer, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size *= 2;
			free(buffer);
			buffer = calloc(size, sizeof(char *));
			if (!buffer)
				return (1);
		}
		else
		{
			free(buffer);
			return (1);
		}
	}
	ft_putendl_fd(buffer, fd);
	return (free(buffer), 0);
}

int	builtin_pwd_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	k;
	int	fd[2];

	i = -1;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[++i].type == RED_IN)
	{
		if (fd[0] == -1)
			return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), ft_putendl_fd(NOF, 2), 1);
		close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
	}
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd[i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), 1);
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
	k = bltin_pwd(fd[1]);
	close_fds(fd);
	return (k);
}

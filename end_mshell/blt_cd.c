/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:47:27 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:47:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	bltin_cd(t_cmd cmd, t_env *env)
{
	if (count_size_args(cmd.args) > 2)
	{
		ft_putendl_fd("bash : cd : too many args", 2);
		return (1);
	}
	if (count_size_args(cmd.args) == 1)
	{
		chdir(ft_getenv("HOME", env));
		return (0);
	}
	if (ft_strncmp(cmd.args[1], "-", IM) == 0)
		return (ft_putendl_fd(ft_getenv("OLDPWD", env), 2), \
chdir(ft_getenv("OLDPWD", env)), 0);
	if (access(cmd.args[1], F_OK) == -1)
	{
		ft_putstr_fd("bash : cd : ", 2);
		ft_putstr_fd(cmd.args[1], 2);
		ft_putendl_fd(" : No such file or directory", 2);
		return (1);
	}
	if (chdir(cmd.args[1]) != 0)
		return (perror("chdir "), 1);
	return (0);
}

int	cd2(t_cmd *cmd, int i[])
{
	return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd[i[0] - 1].path, 2), \
	ft_putendl_fd(": No such file or directory", 2), 127);
}

void	cd3(t_env **env, char *str[], char cwd[], int fd[])
{
	(*env) = change_env(ft_strdup(str[0]), env, "OLDPWD");
	(*env) = change_env(ft_strdup(cwd), env, "PWD");
	close_fds(fd);
}

int	builtin_cd_prep(t_cmd *cmd, t_env **env, char cwd[])
{
	int		fd[2];
	int		i[3];
	char	*str[2];

	i[0] = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i[0]].type == RED_IN)
	{
		if (fd[0] == -1)
			return (cd2(cmd, i));
		close(fd[0]);
		fd[0] = open(cmd[i[0]].path, O_RDONLY);
		(i[0])++;
	}
	if (fd[0] == -1)
		return (cd2(cmd, i));
	i[1] = (i[0])++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i[0]].type != END)
		do1cmd2b(fd, &(i[0]), cmd, env);
	if (fd[1] == -1)
		return (ev2(fd, i, cmd, env));
	str[0] = ft_getenv("PWD", *env);
	i[2] = bltin_cd(cmd[i[1]], *env);
	return (getcwd(cwd, 1024), cd3(env, str, cwd, fd), i[2]);
}

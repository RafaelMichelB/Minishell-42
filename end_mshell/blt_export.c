/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:48:41 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:48:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	o(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '=')
			return (0);
	}
	return (1);
}

int	bltin_export2(t_cmd cmd, t_env **env, int size)
{
	int		n;
	char	**split;

	n = 0;
	while (++n < size)
	{
		if (a_(cmd.args[n]) == 0 || ob(cmd.args[n]) == 1 || o(cmd.args[n]) == 1)
			return (ft_putstr_fd("bash: export: ", 2), \
ft_putstr_fd(cmd.args[n], 2), ft_putendl_fd(": not a valid identifier", 2), 1);
		if (is_in_str('=', cmd.args[n]))
		{
			split = ft_split1(cmd.args[n], '=');
			remove_env(env, split[0]);
			if (split[1])
				add_env_line(env, init_env_line(ft_strdup(split[0]), \
				ft_strdup(split[1])));
			else
				add_env_line(env, init_env_line(ft_strdup(split[0]), \
				NULL));
			ft_free(split);
		}
		else
			add_env_line(env, init_env_line(ft_strdup(cmd.args[n]), NULL));
	}
	return (0);
}

int	ex2(t_env *cp, int fd)
{
	ft_putstr_fd("=\"", fd);
	if (ft_strncmp(cp->key, "_", 2) == 0)
		ft_putstr_fd("/usr/bin/env", fd);
	else
		ft_putstr_fd(cp->value, fd);
	ft_putstr_fd("\"\n", fd);
	return (0);
}

int	bltin_export(t_cmd cmd, t_env **env, int fd)
{
	int		size[2];
	t_env	*cp;
	t_env	*cpy;

	size[0] = count_size_args(cmd.args);
	if (*env == NULL)
		return (1);
	cp = order_env(*env);
	cpy = cp;
	if (size[0] == 1)
	{
		while (cp)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(cp->key, fd);
			if (cp->value)
				ex2(cp, fd);
			else
				ft_putstr_fd("\n", fd);
			cp = cp->next;
		}
	}
	else
		return (env_clear(&cpy), bltin_export2(cmd, env, size[0]));
	return (env_clear(&cpy), 0);
}

int	builtin_export_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	j;
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
	k = bltin_export(cmd[j], env, fd[1]);
	return (close_fds(fd), k);
}

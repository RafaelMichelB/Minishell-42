/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:48:51 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:48:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_unset(t_env *tc)
{
	free(tc->key);
	free(tc->value);
	free(tc);
}

int	bltin_unset(t_cmd cmd, t_env **env)
{
	int		i;
	t_env	*cp;
	t_env	*to_clear;

	i = 0;
	while (cmd.args[++i])
	{
		cp = *env;
		while (cp)
		{
			if (cp->next && ft_strncmp(cp->next->key, cmd.args[i], IM) == 0)
			{
				to_clear = cp->next;
				cp->next = cp->next->next;
				free_unset(to_clear);
			}
			else if (!cp->next && ft_strncmp(cp->key, cmd.args[i], IM) == 0)
			{
				free_unset(to_clear);
				cp = NULL;
			}
			cp = cp->next;
		}
	}
	return (0);
}

void	blt_us2(int fd[], int i, t_cmd *cmd)
{
	if (fd[0] == -1 && access(cmd[i - 1].path, F_OK) != 0)
		return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), ft_putendl_fd(NOF, 2));
	if (fd[0] != -1)
		close(fd[0]);
	fd[0] = open(cmd[i].path, O_RDONLY);
}

int	blt_us3(int fd[], t_cmd *cmd, int i, t_env **env)
{
	(void)env;
	return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), ft_putendl_fd(": Permission denied", 2), \
close(fd[0]), 1);
}

int	builtin_unset_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	j;
	int	k;
	int	fd[2];

	i = -1;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[++i].type == RED_IN)
		blt_us2(fd, i, cmd);
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd[i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), 1);
	j = i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2b(fd, &i, cmd, env);
	if (fd[1] == -1)
	{
		if (access(cmd[i - 1].path, F_OK) == 0 && \
access(cmd[i - 1].path, W_OK) != 0)
			return (blt_us3(fd, cmd, i, env));
		return (close(fd[0]), 1);
	}
	k = bltin_unset(cmd[j], env);
	return (close_fds(fd), k);
}

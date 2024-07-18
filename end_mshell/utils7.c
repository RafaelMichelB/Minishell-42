/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:51:17 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:51:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	a_(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
	}
	return (1);
}

int	ob(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
	}
	return (1);
}

void	do1cmd2b(int fd[], int *i, t_cmd *cmds, t_env **env)
{
	(void)env;
	if (fd[1] == -1)
	{
		*i += 1;
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[*i - 2].path, 2), \
		ft_putendl_fd(": Permission denied", 2));
	}
	if (fd[1] != -1)
		close(fd[1]);
	if (cmds[*i].type == RED_OUT)
		fd[1] = open(cmds[*i].path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd[1] = open(cmds[*i].path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	(*i)++;
}

int	docmdb(t_cmd *c[], int i, char **env, int fd[])
{
	if (ft_strncmp(c[0][i].path, "", 2147483647) == 0)
		return (do1cmd5(c[1], c[0], env, fd));
	return (close(fd[0]), do1cmd41(c[1], c[0], i, env), 0);
}

void	main12b(char *str, t_env **my_env, int *flag)
{
	free(str);
	rl_clear_history();
	(void)my_env;
	ft_putendl_fd("Not matching quotes", 2);
	*flag = 2;
}

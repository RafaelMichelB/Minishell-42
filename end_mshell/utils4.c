/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:59 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:50:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd	handle_hdoc(t_list **l, t_env *menv)
{
	t_cmd	cmd;
	char	**env;

	env = convert_array(menv);
	if (is_in_str('/', (*l)->content) == 0)
		cmd.path = find_nice_path((*l)->content, env);
	else
	{
		if (((char *)((*l)->content))[0] == ' ')
			cmd.path = ft_strtrim2((*l)->content, " ");
		else
			cmd.path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
	}
	*l = (*l)->next;
	cmd.args = gen_args(l);
	cmd.type = HDOC;
	ft_free(env);
	return (cmd);
}

t_cmd	handle_hdoc2(t_list **l, t_env *menv)
{
	t_cmd	cmd;
	char	**env;

	env = convert_array(menv);
	if (is_in_str('/', (*l)->content) == 0)
		cmd.path = find_nice_path((*l)->next->next->content, env);
	else
	{
		if (((char *)((*l)->content))[0] == ' ')
			cmd.path = ft_strtrim2((*l)->next->next->content, " ");
		else
			cmd.path = ft_substr((*l)->next->next->content, \
					0, ft_strlen((*l)->next->next->content));
	}
	cmd.args = gen_args(l);
	free(cmd.args[2]);
	cmd.args[2] = NULL;
	cmd.type = HDOC;
	ft_free(env);
	return (cmd);
}

int	detect_builtin(char *str)
{
	char	*s;

	s = ft_strtrim2(str, " ");
	if (ft_strncmp("cd", s, 2147483647) == 0 || \
	ft_strncmp("echo", s, 2147483647) == 0 || \
	ft_strncmp("pwd", s, 2147483647) == 0 || \
	ft_strncmp("unset", s, 2147483647) == 0 || \
	ft_strncmp("export", s, 2147483647) == 0 || \
	ft_strncmp("env", s, 2147483647) == 0 || \
	ft_strncmp("exit", s, 2147483647) == 0)
	{
		free(s);
		return (0);
	}
	free(s);
	return (1);
}

void	clear_cmds(t_cmd *cmds)
{
	int	j;

	j = 0;
	while (cmds[j].type != END)
	{
		free(cmds[j].path);
		if (cmds[j].args)
		{
			ft_free(cmds[j].args);
		}
		j++;
	}
	free(cmds);
}

void	handle_sigint2(int sig)
{
	(void)sig;
	exit(1);
}

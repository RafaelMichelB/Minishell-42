/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:55:30 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/14 02:55:30 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exit(t_parser *data, int i, int er)
{
	int	temp;

	if (return_to_ex(data) == 1)
		return (1);
	if (data->command->cmd_ex[1] != NULL)
	{
		while (data->command->cmd_ex[1][++i] != '\0')
		{
			if (data->command->cmd_ex[1][i] < 48 ||
				data->command->cmd_ex[1][i] > 57)
			{
				return (set_error(data, 0), 1);
			}
		}
		if (ft_atoi(data->command->cmd_ex[1]) >= 256)
			set_error(data,
				(ft_atoi(data->command->cmd_ex[1]) % 256));
		temp = ft_atoi(data->command->cmd_ex[1]);
		free_parser(data, -1);
		exit(temp);
	}
	else
		return (free_parser(data, -1), exit(er), 0);
}

int	return_to_ex(t_parser *data)
{
	int	i;

	i = -1;
	data->cmd_builtin++;
	if (data->size_li != 1)
		return (1);
	while (data->command->cmd_ex[++i] != NULL)
	{
		if (i > 1)
			return (printf("exit error too many arguments\n"), 1);
	}
	return (0);
}

void	free_parser(t_parser *data, int i)
{
	printf("GB W\n");
	if (data->envp != NULL)
		free_split_str(data->envp); // Libère l'envp
	if (data->tab_path != NULL)
		free_split_str(data->tab_path);
	if (data->pipefd != NULL)
	{
		while (++i != data->size_li)
		{
			printf("free data->pipefd[%d] size %d\n", i, data->size_li);
			free(data->pipefd[i]);
		}
		free(data->pipefd);
		data->pipefd = NULL;
	}
	free_command(data);
	free(data);
}

void	free_command(t_parser *data)
{
	t_command	*tmp;

	data->command = data->head_cmd;
	if (data->head_cmd == NULL)
		return ;
	while (data->command != NULL)
	{
		tmp = data->command->next;
		free_insidenode(data->command);
		data->command = tmp;
	}
	data->head_cmd = NULL;
}

void	free_insidenode(t_command *cmd)
{
	printf("\ncmd->line\n%s\n\n", cmd->line);
	if (cmd != NULL && cmd->line != NULL) // line est bien free , sa remonte jusqu'a readline
		free(cmd->line);
	if (cmd->cmd_ex != NULL)
		free_split_str(cmd->cmd_ex);
	if (cmd->flags == 1)
		unlink(".here_doc");
	free(cmd);
}

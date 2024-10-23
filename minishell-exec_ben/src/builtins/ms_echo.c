/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:03:48 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/18 07:03:48 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_echo(t_parser *data, int i, int in, int out)
{
	in = dup(0);
	out = dup(1);
	redir_echo(data);
	if ((data->command->cmd_ex[1] != NULL)
		&& (check_arg(data, data->command->cmd_ex[1], -1) == 1))
	{
		while (data->command->cmd_ex[++i] != NULL)
		{
			printf("%s", data->command->cmd_ex[i]); // ECHO sans \n
			if (data->command->cmd_ex[i + 1] != NULL)
				printf(" ");
		}
	}
	else if (data->command->cmd_ex[1] != NULL)
	{
		while (data->command->cmd_ex[++i] != NULL)
			printf("%s ", data->command->cmd_ex[i]); // ECHO\n
		printf("\n");
	}
	else
		printf("\n");
	dup2(in, 0);
	dup2(out, 1);
	data->cmd_builtin++;
}

int	check_arg(t_parser *data, char *str, int i)
{
	if (str[0] == '-' && str[1] == 'n') //Vérif si l'argument commence par "-n"
	{
		i = 2; // Commence à vérifier après "-n"
		while (str[i] == 'n') // Vérifie s'il y a plusieurs 'n'
			i++;
		if (str[i] == '\0' || str[i] == ' ')
		{
			printf("before supr\n");
			data->command->cmd_ex = suprin_tab(data->command->cmd_ex, 0, 1);
			printf("after supr %s %d\n", data->command->cmd_ex[1], i);
			return (1); // Renvoie 1 pour indiquer la suppression du \n
		}
	}
	return (0); // Renvoie 0 si l'argument n'est pas valide
}

void	redir_echo(t_parser *data)
{
	if (data->command->fd_in > -1)
	{
		dup2(data->command->fd_in, 0);
		close(data->command->fd_in);
		close(data->pipefd[data->index + data->cmd_builtin][0]);
	}
	if (data->command->fd_out > -1)
	{
		dup2(data->command->fd_out, 1);
		close(data->command->fd_out);
		close(data->pipefd[data->index + data->cmd_builtin][1]);
	}
}

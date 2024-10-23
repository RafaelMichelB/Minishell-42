/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:43:04 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/23 23:03:30 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_redir(t_parser *data)
{
	printf("\n\nTest: %d\n%d\n", data->index + data->cmd_builtin, data->size_li);
	if (data->command->fd_in == -2 || data->command->fd_in > -1)
	{
		if (data->command->fd_in == -2)
			return (-1);//perror() fd introuvable
		dup2(data->command->fd_in, 0);
		close(data->command->fd_in);
		close(data->pipefd[data->index + data->cmd_builtin][0]);
	}
	else//pas de redirect
	{
		if ((data->index + data->cmd_builtin) == 0)
		{
			dup2(STDIN_FILENO, 0);
		}
		else
			dup2(data->pipefd[data->index + data->cmd_builtin][0], 0);
		close(data->pipefd[data->index + data->cmd_builtin][0]);
	}
	if (redir_out(data) == -1)
		return (-1);
	return (0);
}

int	redir_out(t_parser *data)
{
	if (data->command->fd_out == -2 || data->command->fd_out > -1)
	{
		if (data->command->fd_out == -2)
			return (-1);
		dup2(data->command->fd_out, 1);
		close(data->command->fd_out);
		close(data->pipefd[data->index + data->cmd_builtin][1]);
	}
	else
	{
		if (data->index + data->cmd_builtin + 1 != data->size_li
			&& data->size_li != 1)
		{
			if (dup2(data->pipefd[data->index + data->cmd_builtin + 1][1]
				, 1) == -1)
				perror("dup2 failed for pipefd write end");
			perror("\nDONE SORTIE 22\n");
		}
		else// if (data->index + data->cmd_builtin == data->size_li 
			//|| data->size_li == 1)
			{
				perror("\nDONE SORTIE\n");
				dup2(STDOUT_FILENO, 1);
			}
		close(data->pipefd[data->index + data->cmd_builtin][1]);
	}
	return (0);
}

void	close_pipe_child(t_parser *data)
{
	int	i;

	i = -1;
	while (++i < data->size_li)
	{
		if (i != data->index)
		{
			close(data->pipefd[i][0]);
			close(data->pipefd[i][1]);
			printf("Fermeture des pipes inutilisés pour i = %d\n", i);
		}
		else
		{
			if ((data->index + data->cmd_builtin) == 0)
			{
				printf("Fermeture de la sortie du pipe de la première commande\n");
				close(data->pipefd[i][1]);
			}
			else if ((data->index + data->cmd_builtin) == data->size_li - 1)
			{
				printf("Fermeture de l'entrée du pipe de la dernière commande\n");
				close(data->pipefd[i][0]);
			}
		}
	}
}

// value -1 = aucune redir
// value -2 = erreur file
// value > -1 = file redir

void	close_pipe(t_parser *data)
{
	int	i;

	i = 0;
	printf("close pipe\n");
	data->command = data->head_cmd;
	while (data->command != NULL)
	{
		if (data->command->fd_in > -1)
		{
			close(data->command->fd_in);
		}
		if (data->command->fd_out > -1)
		{
			close(data->command->fd_out);
		}
		data->command = data->command->next;
	}
	while (i != data->size_li)
	{
		printf("fermeture pipe parent %d entre - sortie\n", i);
		close(data->pipefd[i][0]);
		close(data->pipefd[i][1]);
		i++;
	}
}

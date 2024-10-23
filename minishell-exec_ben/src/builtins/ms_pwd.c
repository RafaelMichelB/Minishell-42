/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:20:56 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/22 13:20:56 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_parser *data, pid_t *pid)
{
	char	path[1028];

	pid[data->index + data->cmd_builtin] = fork();
	if (pid[data->index + data->cmd_builtin] == 0)
	{
		if (pipe_redir(data) == -1)
			return (set_error(data, 126), perror("fd"), 1);
		close_pipe_child(data);
		getcwd(path, 1028);
		printf("%s\n", path);
		free(pid);
		free_parser(data, -1);
		exit(0);
	}
	waitpid(pid[data->index + data->cmd_builtin], &data->status, 0);
	data->index++;
	return (0);
}

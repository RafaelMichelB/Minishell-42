/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:33:18 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/23 22:44:15 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_ex_utils(t_parser *data)
{
	// data->handle_error = 0;// dois recup le code erreur
	data->tab_path = NULL;
	data->pipefd = NULL;
	data->size_li = ft_size(&data->command);
	printf("size li %d\n", data->size_li);
	printf("data->command->cmd_ex[0] = %s\n", data->command->cmd_ex[0]);
	data->index = 0;
	init_pipe(data, 0);
	data->index = 0;
	data->status = 0;
	data->cmd_builtin = 0;
	data->ipid = 0;
	return (0);
}

//attention pour les free , condition d'arret
int	init_pipe(t_parser *data, int i)
{
	printf("start of init_pipe\n");
	data->pipefd = (int **)malloc(sizeof(int *) * (data->size_li + 1));
	//attention + 1 regle segfault
	if (data->pipefd == NULL)
		printf("erreur malloc\n");
	while (i != data->size_li)
	{
		data->pipefd[i] = (int *)malloc(sizeof(int *) * 2);
		if (data->pipefd[i] == NULL)
			return (printf("erreur malloc I\n"), 1);
		if (pipe(data->pipefd[i]) == -1)
			return (write(1, "error pipe\n", 11), 1);
		i++;
	}
	return (0);
}

void	init_envp(t_parser *data, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (env[len] != NULL)
		len++;
	data->envp = (char **)malloc(sizeof (char *) * (len + 1));
	while (env[++i] != NULL)
		data->envp[i] = ft_strdup(env[i]);
	data->envp[len] = NULL;
}

/*void	init_cmdtab(t_parser *data)
{
	char	*str;

	str = NULL;
	if (data->command_table->command->arguments != NULL)
	{
		str = joinspace(data->command_table->command->command,
				data->command_table->command->arguments);
		data->command_table->command->cmd_ex = split_str(str, ' ');
	}
	else
		data->command_table->command->cmd_ex
			= split_str(data->command_table->command->command, ' ');
	if (str != NULL)
		free(str);
}*/
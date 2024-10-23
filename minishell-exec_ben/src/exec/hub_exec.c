/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:10:52 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/23 23:07:40 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fonction central manage les données
void	hub_exec(t_parser *data)
{
	pid_t	*pid;

	printf("start hub\n");
	if (init_ex_utils(data) == 1)
	{
		data->handle_error = 1;
		return ;
	}
	pid = malloc(sizeof (pid_t) * data->size_li);
	printf("before exec\n");
	exec(data, pid);
	printf("finish total\n");
	// freetab_path(data);
	free_ex(data);
	printf("apres free_ex\n");
	return ;
}

int	exec(t_parser *data, pid_t *pid)
{
	printf("start exec\n");
	while ((data->index + data->cmd_builtin) != data->size_li)
	{
		data->tab_path = finding_path(data);
		if (cmd_builtin(data, &pid[data->index + data->cmd_builtin]) == 1) // si cmd == builtin , exec builtin -> next
			data->command = data->command->next;
		else
		{
			pid[data->index] = fork();
			if (pid[data->index] == 0)
				children(data);
			data->command = data->command->next;
			data->index++;
		}
		printf("fin de boucle exec\n");
		//usleep(10);
	}
	printf("APRES LA BOUCLE\n");
	close_pipe(data);
	while (data->index-- != 0)
	{
		printf("WAIT PID %d\n", data->index);
		waitpid(pid[data->index], &data->status, 0);
	}
	return (free(pid), 0);
}

//prendre en compte le cas ou erreur cmd , sa dois effectue les autres cmd mais pas les affiches ou dans des redir si y a

//process pour les exec built-in
//probleme struct en attente de la struc final 
//ATTENTION les built-in qui modifie l'env parent sont a faire dans le parent
//Les built-in qui ne modifie pas doivent etre fait dans un fork pour transmettre via le pipe
int	cmd_builtin(t_parser *data, pid_t *pid)
{
	if (compare(data->command->cmd_ex[0], "env") == 0)
		if (ms_env(data, pid, -1) == 0)
			return (1);
	if (compare(data->command->cmd_ex[0], "pwd") == 0)
		if (ms_pwd(data, pid) == 0)
			return (1);
	if (compare(data->command->cmd_ex[0], "cd") == 0)
		if (ms_cd(data) == 0) /*, pid*/
			return (1);
	if (compare(data->command->cmd_ex[0], "export") == 0)
		return (ms_export(data, 0), 1);
	if (compare(data->command->cmd_ex[0], "unset") == 0)
		return (ms_unset(data, -1, 0), 1);
	if (compare(data->command->cmd_ex[0], "exit") == 0)
		return (ms_exit(data, -1, data->handle_error), 1); // PROBLEME a check
	if (compare(data->command->cmd_ex[0], "echo") == 0) // complique a finir sans la structure avec le parsing
		return (ms_echo(data, 0, 0, 0), 1);
	return (0);
}

int	children(t_parser *data)
{
	printf("start children %d\n", (data->index + data->cmd_builtin));
	if (pipe_redir(data) == -1) //	need to handle the multi fd
		return (set_error(data, 126), perror("fd"), 1);
	close_pipe_child(data);
	data->validpath = checkaccess(data->command->cmd_ex[0], data->tab_path);
	if (data->validpath == NULL)
		return (set_error(data, 127), perror("access"), 1);
	// init_cmdtab(data);//peu etre plus besoin , char **cmd_esteban
	printf("finish children %d\n", (data->index + data-> cmd_builtin));
	printf("%s", data->envp[2]);
	execve(data->validpath, data->command->cmd_ex, data->envp);
	return (set_error(data, 1), 1);
}

char	**finding_path(t_parser *data)
{
	int		i;
	char	*path;
	char	**tab_path;

	printf("start findingpath\n");
	i = 0;
	if (data->tab_path != NULL)
		freetab_path(data);
	while (data->envp[i] != NULL)
	{
		if (ft_strncmp(data->envp[i], 4) == 1)
			break ;
		i++;
	}
	//TODO : gere le cas ou le path est supr
	path = ft_strdup(data->envp[i] + 5);
	tab_path = split_str(path, ':');
	free(path);
	printf("return of findingpath\n");
	return (tab_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:36:06 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/17 08:36:06 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pars.h"

void	sigint(int sign)//ctrl-C
{
	sign = 0;
	printf("\n");
	rl_on_new_line();// Réinitialiser la ligne
	rl_replace_line("", 0);// Effacer la ligne en cours dans `readline`
	rl_redisplay();
}

void	init_sign(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_main(t_parser *data, char **env, int argc)
{
	int	i;

	i = -1;
	(void)argc;
	init_sign();
	init_envp(data, env);
	data->handle_error = 0;
	data->tab_path = NULL;
	data->pipefd = NULL;
	data->head_cmd = NULL;
	while (data->envp[++i] != NULL)
	{
		if (compare_str(data->envp[i], "SHLVL", 5) == 0)
			data->envp[i][ft_strlen(data->envp[i]) - 1] 
				= data->envp[i][ft_strlen(data->envp[i]) - 1] + 1;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_parser		*data;
	t_command		*command;

	(void)argv;
	data = malloc(sizeof(t_parser));
	init_main(data,/* &command,*/ env, argc);
	while (1)
	{
		command = ft_init_node();
		command->line = readline("MINISHELL:");
		if (command->line == NULL) //ctrl-D
			return (printf("exit\n"), free_parser(data, -1), free(command), 0);
		else
		{
			add_history(command->line);
			if (verif_parse(command->line) == 1)
				continue;
			ft_parse_line(command, data);
			printf("\nis ok parse_line main\n");
			hub_exec(data);
		}
		// free_parse(); free de la lst
	}
	return (/*free_all(data), */0);//free le reste pas deja free
}

int	verif_parse(char *line)
{
	if (ft_check_pipe_empty(line) == 1 ||
			ft_check_redir_empty(line) == 1 ||
			ft_check_close_quote(line))
				// NEED TO CHECK IN CLOSE QUOTE IF THE ACTUAL QUOTE IS BETWEEN SIMPLE OR DOUBLE QUOTE AND NOTE INCREMENT
				// THE BEFORE AND AFTER FLAG 
				// FOR EXEMPLE : echo "'coucou" hello | wc '-l' should'nt an error syntax
	{
		printf("error syntax\n");
		free(line);
		return (1);
	}
	return (0);
}

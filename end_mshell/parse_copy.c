/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:01 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:50:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

int	hold_flag(char c, int flag)
{
	static int	f = -1;

	if (c == 'p')
	{
		f = flag;
	}
	return (f);
}

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int		check_errors(char *str)
{
	int	i;
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && dq == 0 && sq == 0)
			dq = 1;
		else if (str[i] == '"' && dq == 1)
			dq = 0;
		else if (str[i] == '\'' && dq == 0 && sq == 0)
			sq = 1;
		else if (str[i] == '\'' && sq == 1)
			sq = 0;
		i++;
	}
	return (dq == 0 && sq == 0);
}
void	read_entry(char *str, t_env **my_env, int *flag, char **t)
{
	int	fd;

	str = readline("[Minishell] > ");
	*flag = hold_flag('g', -1);
	if (!str)
		main12(str, my_env, *flag);
	if (check_errors(str) == 0)
		return (main12b(str, my_env, flag));
	else if (str && str[0] != '\0')
		add_history(str);
	t = ft_split(str, ' ');
	if (is_in_str('|', str) == 0 && t[0] && ft_strncmp(t[0], "exit", 5) == 0)
		return (main13(&t, *flag, str, my_env), ft_free(t));
	else
	{
		ft_free(t);
		if (only_in2(str, ' ', '	') == 1)
			return ;
		fd = -1;
		main2(str, my_env, flag, fd);
		unlink("/tmp/tempfile");
		unlink("/tmp/tempfile2");
		free(str);
		*flag = hold_flag('p', *flag);
	}
}

int	main(int c, char **v, char **env)
{
	char	*str;
	t_env	*my_env;
	char	**t;
	int		flag;

	if (c != 1)
		return (1);
	(void)v;
	str = NULL;
	t = NULL;
	my_env = generate_env(env);
	my_env = change_env(ft_itoa(ft_atoi(ft_getenv("SHLVL", my_env)) + 1), \
	&my_env, "SHLVL");
	flag = hold_flag('p', 0);
	while (1)
	{
		init_signal();
		read_entry(str, &my_env, &flag, t);
		unlink("/tmp/heredoc_file");
	}
}

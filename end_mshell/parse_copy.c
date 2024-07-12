#include "parser.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

void	init_signal(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	read_entry(char *str, t_env **my_env, int *flag, char **t)
{
	int	fd;

	str = readline("[Minishell] > ");
	if (!str)
		main12(str, my_env, *flag);
	if (str && str[0] != '\0')
		add_history(str);
	t = ft_split(str, ' ');
	if (t[0] && ft_strncmp(t[0], "exit", 5) == 0)
	{
		main13(&t, *flag, str, my_env);
		ft_free(t);
	}
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
	}
}

int	main(int c, char **v, char **env)
{
	int		flag;
	char	*str;
	t_env	*my_env;
	char	**t;

	if (c != 1)
		return (1);
	(void)v;
	str = NULL;
	t = NULL;
	my_env = generate_env(env);
	my_env = change_env(ft_itoa(ft_atoi(ft_getenv("SHLVL", my_env)) + 1), \
	&my_env, "SHLVL");
	flag = 0;
	while (1)
	{
		init_signal();
		read_entry(str, &my_env, &flag, t);
		unlink("/tmp/heredoc_file");
	}
}

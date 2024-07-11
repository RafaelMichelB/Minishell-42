#include "parser.h"
#include "Pipex/inc/pipex_bonus.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	*sim_glob(char c, t_env **env, t_cmd *cmd, void *n)
{
	static t_env	**e = NULL;
	static t_cmd	*cm = NULL;
	static int	*nb = NULL;
	static char	**str = NULL;

	if (c == 'c')
	{
		e = env;
		cm = cmd;
	}
	else if (c == 'v')
		nb = (int *)n;
	else if (c == 'w')
		str = (char **)n;
	else if (c == 'e')
		return (e);
	else if (c == 'm')
		return (cm);
	else if (c == 'n')
		return (nb);
	else if (c == 'o')
		return (str);
	else if (c == 'h')
		nb[0] == -10;
	else if (c == 'i')
		nb[0] == 0;
}
void	handle_sigint3(int sig)
{
	t_cmd	*cmd;
	t_env	**env;
	int	*nb;
	char	**st;

	(void)sig;
	cmd = sim_glob('m', NULL, NULL, NULL);
	env = sim_glob('e', NULL, NULL, NULL);
	nb = sim_glob('n', NULL, NULL, NULL);
	st = sim_glob('o', NULL, NULL, NULL);
	if (cmd)
		clear_cmds(cmd);
	if (env)
		env_clear(env);
	if (nb)
		free(nb);
	if (st)
		ft_free(st);
	ft_putendl_fd("CTRL+C hdocs pressé", 2);
	exit(3);
}


void	handle_sigint4(int sig)
{
	int *n;

	(void)sig;
	n = sim_glob('n', NULL, NULL, NULL);
	n[0] = -10;
	sim_glob('v', NULL, NULL, n);
	ft_putendl_fd("CTRL+C hdocs pressé no ex", 2);
}

int	handle_hdocs(char *end_w, t_cmd *cmds, int j, t_env **env)
{
	int	fd;
	int	status;
	char	*input;
	char	**arr;
	pid_t	pid;

	signal(SIGINT, handle_sigint3);
	sim_glob('c', env, cmds, NULL);
	pid = fork();
	if (pid == 0)
	{
		arr = ft_calloc(2, sizeof(char *));
		sim_glob('w', NULL, NULL, arr);
		fd = open("heredoc_file", O_RDWR | O_TRUNC);
		input = readline("> ");
		while (input != NULL && ft_strncmp(end_w, input, 2147483647) != 0)
		{
			ft_putendl_fd(input, fd);
			input = readline("> ");
		}
		if (input == NULL)
		{
			//ft_putendl_fd("Hey", 2);
			free(cmds[0].path);
			cmds[0].path = NULL;
			cmds[0].type = ENDT;
			return (0);
		}
		ft_free(cmds[j].args);
		free(cmds[j - 1].path);
		cmds[j - 1].path = ft_strdup("heredoc_file");
		arr[0] = ft_strdup(cmds[j].path);
		arr[1] = NULL;
		cmds[j].args = arr;
		cmds[j].type = CMD;
		close(fd);
	}
	else
	{
		signal(SIGINT, handle_sigint4);
		waitpid(pid, &status, 0);
		env_clear(env);
		//clear_cmds(cmds);
		//ft_putendl_fd("HEYA", 2);
		//free(sim_glob('n', NULL, NULL, NULL));
		//sim_glob('h', NULL, NULL, NULL);
		return (0); //exit(0); // 
	}
	return (0);
}

int	*find_hdocs(t_cmd *cmd, int n)
{
	int	*hdocs;
	int	nb;

	nb = 0;
	while (cmd[n].type != END)
	{
		if (cmd[n].type == HDOC)
			nb++;
		n++;
	}
	hdocs = ft_calloc(nb + 1, sizeof(int));
	hdocs[nb] = -1;
	n = 0;
	nb = 0;
	while (cmd[n].type != END)
	{
		if (cmd[n].type == HDOC)
		{
			hdocs[nb]  = n;
			nb++;
		}
		n++;
	}
	return (hdocs);
}
/*
int	main( void )
{
	t_cmd	*cmd = ft_calloc(4, sizeof(t_cmd));
	int	*j;
	int	i;
	char	**tab = ft_calloc(3, sizeof(char *));

	tab[0] = ft_strdup(";");
	tab[1] = ft_strdup("EOF");
	tab[2] = NULL;
	i = -1;
	cmd[0].path = ft_strdup("tempfile");
	cmd[0].args = NULL;
	cmd[0].type = RED_IN;
	cmd[1].path = ft_strdup("/usr/bin/cat");
	cmd[1].args = tab;
	cmd[1].type = HDOC;
	cmd[2].path = ft_strdup("tempfile2");
	cmd[2].args = NULL;
	cmd[2].type = RED_OUT;
	cmd[3].type = END;

	j = find_hdocs(cmd, 0);
	while (j[++i] != -1)
		handle_hdoc((cmd[j[i]].args)[1], cmd, j[i]);
	i = 0;
	while (cmd[i].type != END)
	{
		ft_putstr_fd(cmd[i].path, 2);
		ft_putstr_fd("||", 2);
		if (cmd[i].args)
		{
			ft_putstr_fd((cmd[i].args)[0], 2);
			ft_putstr_fd("||", 2);
		}
		ft_putstr_fd("\n", 2);
		i++;
	}
}*/

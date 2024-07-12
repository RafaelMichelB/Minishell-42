#include "parser.h"
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
	static int		*nb = NULL;
	static char		**str = NULL;

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
	return (NULL);
}

void	handle_sigint3(int sig)
{
	t_cmd	*cmd;
	int		*nb;
	char	**st;

	(void)sig;
	cmd = sim_glob('m', NULL, NULL, NULL);
	nb = sim_glob('n', NULL, NULL, NULL);
	st = sim_glob('o', NULL, NULL, NULL);
	if (cmd)
		clear_cmds(cmd);
	if (nb)
		free(nb);
	if (st)
		ft_free(st);
	exit(3);
}

void	handle_sigint4(int sig)
{
	int	*n;

	(void)sig;
	n = sim_glob('n', NULL, NULL, NULL);
	n[0] = -10;
	sim_glob('v', NULL, NULL, n);
	signal(SIGINT, handle_sigint);
}

void	hd3(t_cmd *cmds, int j, char **arr)
{
	ft_free(cmds[j].args);
	free(cmds[j - 1].path);
	cmds[j - 1].path = ft_strdup("/tmp/heredoc_file");
	arr[0] = ft_strdup(cmds[j].path);
	arr[1] = NULL;
	cmds[j].args = arr;
	cmds[j].type = CMD;
}

void	hd2(char **arr, t_cmd *cmds, int j, char *end_w)
{
	char	*input;
	int		fd;

	arr = ft_calloc(2, sizeof(char *));
	sim_glob('w', NULL, NULL, arr);
	fd = open("/tmp/heredoc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	input = readline("> ");
	while (input != NULL && ft_strncmp(end_w, input, 2147483647) != 0)
	{
		ft_putendl_fd(input, fd);
		input = readline("> ");
	}
	if (input == NULL)
	{
		free(cmds[0].path);
		cmds[0].path = NULL;
		cmds[0].type = ENDT;
		return ;
	}
	hd3(cmds, j, arr);
	close(fd);
}

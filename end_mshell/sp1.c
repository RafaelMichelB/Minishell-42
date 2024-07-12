#include "parser.h"

void	simulpipe2(int tab[], t_cmd *cmd, t_cmd **type)
{
	while (cmd[tab[0]].type == RED_IN)
	{
		tab[1]++;
		tab[0]++;
	}
	while (cmd[tab[0]].type != RED_IN && cmd[tab[0]].type != END)
	{
		tab[0]++;
		tab[1]++;
	}
	(*type) = ft_calloc(tab[1] + 1, sizeof(t_cmd));
	(*type)[tab[1]].type = END;
	tab[1] = 0;
	while (cmd[tab[2]].type == RED_IN)
	{
		(*type)[tab[1]] = cmd[tab[2]];
		tab[1]++;
		tab[2]++;
	}
	while (cmd[tab[2]].type != RED_IN && cmd[tab[2]].type != END)
	{
		(*type)[tab[1]] = cmd[tab[2]];
		tab[2]++;
		tab[1]++;
	}
}

int	handle_hdocs(char *end_w, t_cmd *cmds, int j, t_env **env)
{
	int		status;
	char	**arr;
	pid_t	pid;

	arr = NULL;
	signal(SIGINT, handle_sigint3);
	sim_glob('c', env, cmds, NULL);
	pid = fork();
	if (pid == 0)
		return (hd2(arr, cmds, j, end_w), 0);
	else
	{
		signal(SIGINT, handle_sigint4);
		waitpid(pid, &status, 0);
		return (signal(SIGINT, handle_sigint), 0);
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
			hdocs[nb] = n;
			nb++;
		}
		n++;
	}
	return (hdocs);
}

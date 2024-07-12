#include "parser.h"

void	sp(int tab[], t_env **env, t_cmd *type)
{
	tab[4] = 1;
	if (ft_strncmp(type[tab[3]].path, "cd", 2147483647) == 0)
		tab[6] = builtin_cd_prep(type, env);
	else if (ft_strncmp(type[tab[3]].path, "echo", 2147483647) == 0)
		tab[6] = builtin_echo_prep(type);
	else if (ft_strncmp(type[tab[3]].path, "pwd", 2147483647) == 0)
		tab[6] = builtin_pwd_prep(type);
	else if (ft_strncmp(type[tab[3]].path, "unset", 2147483647) == 0)
		tab[6] = builtin_unset_prep(type, env);
	else if (ft_strncmp(type[tab[3]].path, "env", 2147483647) == 0)
		tab[6] = builtin_env_prep(type, env);
	else if (ft_strncmp(type[tab[3]].path, "export", 2147483647) == 0)
		tab[6] = builtin_export_prep(type, env);
	free(type);
}

int	sp2(int tab[], t_cmd *cmd, t_env **env)
{
	tab[0] = 0;
	while (cmd[tab[0]].type != END)
	{
		free(cmd[tab[0]].path);
		if (cmd[tab[0]].args)
			ft_free(cmd[tab[0]].args);
		(tab[0])++;
	}
	free(cmd);
	if (tab[5] == 1)
	{
		env_clear(env);
		if (tab[4] == 1)
			exit(tab[6]);
		else
			exit(WEXITSTATUS(tab[6]));
	}
	else
	{
		if (tab[4] == 1)
			return (tab[6]);
		else
			return (WEXITSTATUS(tab[6]));
	}
}

void	sp3(int tab[], t_env **env, t_cmd *type, t_cmd *cmd)
{
	char	**nenv;
	pid_t	pid;

	if (type[tab[3]].type == BUILTIN)
		sp(tab, env, type);
	else
	{
		tab[4] = 0;
		nenv = convert_array(*env);
		pid = fork();
		if (pid == 0)
		{
			env_clear(env);
			do1cmd(type, nenv, cmd, 0);
		}
		else
		{
			waitpid(pid, &(tab[6]), 0);
			free(type);
			ft_free(nenv);
		}
	}
}

void	sp4(int tab[], t_cmd *cmd, t_cmd *type, t_env **env)
{
	tab[2] = tab[0];
	tab[1] = 0;
	simulpipe2(tab, cmd, &type);
	tab[3] = 0;
	while (type[tab[3]].type == RED_IN)
		tab[3]++;
	sp3(tab, env, type, cmd);
}

int	simulpipe(t_cmd *cmd, t_env **env)
{
	int		tab[8];
	int		*j;
	t_cmd	*type;

	type = NULL;
	tab[6] = 0;
	tab[4] = 0;
	tab[5] = find_hdoc2(cmd);
	tab[7] = -1;
	j = find_hdocs(cmd, 0);
	sim_glob('v', NULL, NULL, j);
	while (j[++(tab[7])] != -1)
		handle_hdocs((cmd[j[tab[7]]].args)[1], cmd, j[tab[7]], env);
	free(j);
	tab[0] = 0;
	if ((cmd)[tab[0]].type == ENDT)
		return (clear_cmds(cmd), ft_free(sim_glob('o', NULL, NULL, NULL)), \
		env_clear(env), exit(tab[6]), 0);
	while ((cmd)[tab[0]].type != END)
	{
		if ((cmd)[tab[0] + 1].type == HDOC)
			return (clear_cmds(cmd), tab[6]);
		sp4(tab, cmd, type, env);
	}
	return (sp2(tab, cmd, env));
}

#include "parser.h"

void	free_unset(t_env *tc)
{
	free(tc->key);
	free(tc->value);
	free(tc);
}

int	bltin_unset(t_cmd cmd, t_env **env)
{
	int		i;
	t_env	*cp;
	t_env	*to_clear;

	i = 0;
	while (cmd.args[++i])
	{
		cp = *env;
		while (cp)
		{
			if (cp->next && ft_strncmp(cp->next->key, cmd.args[i], IM) == 0)
			{
				to_clear = cp->next;
				cp->next = cp->next->next;
				free_unset(to_clear);
			}
			else if (!cp->next && ft_strncmp(cp->key, cmd.args[i], IM) == 0)
			{
				free_unset(to_clear);
				cp = NULL;
			}
			cp = cp->next;
		}
	}
	return (0);
}

int	builtin_unset_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	j;
	int	k;
	int	fd[2];

	i = -1;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[++i].type == RED_IN)
	{
		if (fd[0] == -1)
			return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), ft_putendl_fd(NOF, 2), 1);
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
	}
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd[i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), 1);
	j = i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	k = bltin_unset(cmd[j], env);
	return (close_fds(fd), k);
}

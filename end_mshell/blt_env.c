#include "parser.h"

int	bltin_env(t_env *env, int fd)
{
	while (env)
	{
		if (ft_strncmp(env->key, "_", 1) == 0)
			ft_putstr_fd("_=/usr/bin/env\n", fd);
		else if (env->value)
		{
			ft_putstr_fd(env->key, fd);
			ft_putstr_fd("=", fd);
			ft_putendl_fd(env->value, fd);
		}
		env = env->next;
	}
	return (0);
}

int	builtin_env_prep(t_cmd *cmd, t_env **env)
{
	int	i[3];
	int	fd[2];

	i[0] = -1;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[++(i[0])].type == RED_IN)
	{
		if (fd[0] == -1)
			return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i[0] - 1].path, 2), ft_putendl_fd(NOF, 2), 1);
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i[0]].path, O_RDONLY);
	}
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i[0] - 1].path, 2), ft_putendl_fd(NOF, 2), 1);
	i[1] = (i[0])++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i[0]].type != END)
		do1cmd2(fd, &(i[0]), cmd);
	if (count_size_args(cmd[i[1]].args) > 1)
		return (1);
	i[2] = bltin_env(*env, fd[1]);
	return (close_fds(fd), i[2]);
}

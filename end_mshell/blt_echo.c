#include "parser.h"

void	escape_print(char c, int fd)
{
	ft_putstr_fd("\\", fd);
	ft_putchar_fd(c, fd);
}

void	print_arg(char *arg, int fd)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			escape_print(arg[i], fd);
		}
		else
			ft_putchar_fd(arg[i], fd);
		i++;
	}
}

void	bltin_echo(t_cmd cmd, int fd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (ft_strncmp(cmd.args[1], "-n", 10) == 0)
	{
		if (count_size_args(cmd.args) <= 2)
			return ;
		new_line = 0;
		i = 2;
	}
	while (i < count_size_args(cmd.args))
	{
		print_arg(cmd.args[i], fd);
		i++;
		if (i < count_size_args(cmd.args))
			ft_putstr_fd(" ", fd);
	}
	if (new_line == 1)
		ft_putstr_fd("\n", fd);
}

int	builtin_echo_prep(t_cmd *cmd)
{
	int	i;
	int	j;
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
	if (count_size_args(cmd[j].args) == 1)
		return (ft_putstr_fd("\n", fd[1]), 0);
	return (bltin_echo(cmd[j], fd[1]), close_fds(fd), 0);
}

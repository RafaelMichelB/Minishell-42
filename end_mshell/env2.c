#include "parser.h"

t_env	*generate_env(char **env)
{
	char	**split;
	t_env	*my_env;
	int		i;

	i = 0;
	my_env = NULL;
	while (env[i])
	{
		split = ft_split1(env[i], '=');
		if (split[1])
			add_env_line(&my_env, init_env_line(ft_strdup(split[0]), \
						ft_strdup(split[1])));
		else
			add_env_line(&my_env, init_env_line(ft_strdup(split[0]), \
						ft_strdup("")));
		i++;
		ft_free(split);
	}
	return (my_env);
}

t_env	*generate_env2(char **env)
{
	char	**split;
	t_env	*my_env;
	int		i;

	i = 0;
	my_env = NULL;
	while (env[i])
	{
		split = ft_split1(env[i], '=');
		if (split[1])
			add_env_line(&my_env, init_env_line(ft_strdup(split[0]), \
						ft_strdup(split[1])));
		else
			add_env_line(&my_env, init_env_line(ft_strdup(split[0]), NULL));
		i++;
		ft_free(split);
	}
	return (my_env);
}

int	envsize(t_env *env)
{
	int	s;

	s = 0;
	while (env)
	{
		s++;
		env = env->next;
	}
	return (s);
}

void	dc(int fd[], int *i, t_cmd *cmds)
{
	signal(SIGINT, handle_sigint2);
	do1cmd32(fd, i, cmds);
}

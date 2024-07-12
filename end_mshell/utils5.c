#include "parser.h"

void	close_fds(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

char	*ft_getenv(char *s, t_env *env)
{
	while (env)
	{
		if (ft_strncmp(s, env->key, 2147483647) == 0)
			return (env->value);
		env = env->next;
	}
	return ("");
}

int	count_size_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		i++;
	}
	return (i);
}

t_env	*change_env(char *s, t_env **env, char *s2)
{
	t_env	*cp;
	t_env	*cpy;

	cp = *env;
	cpy = NULL;
	while (cp)
	{
		if (ft_strncmp((cp)->key, s2, 2147483647) == 0)
			add_env_line(&cpy, init_env_line(ft_strdup((cp)->key), s));
		else
		{
			if ((cp)->value)
				add_env_line(&cpy, init_env_line(ft_strdup((cp)->key), \
				ft_strdup((cp)->value)));
			else
				add_env_line(&cpy, init_env_line(ft_strdup((cp)->key), \
				NULL));
		}
		cp = (cp)->next;
	}
	env_clear(env);
	return (cpy);
}

void	remove_env(t_env **env, char *str)
{
	t_env	*cp;
	t_env	*to_clear;

	cp = *env;
	while (cp)
	{
		if (cp->next && ft_strncmp(cp->next->key, str, 2147483647) == 0)
		{
			to_clear = cp->next;
			cp->next = cp->next->next;
			free(to_clear->key);
			free(to_clear->value);
			free(to_clear);
		}
		else if (cp->next == NULL && ft_strncmp(cp->key, str, 2147483647) == 0)
		{
			free(cp->key);
			free(cp->value);
			free(cp);
			cp = NULL;
		}
		cp = cp->next;
	}
}

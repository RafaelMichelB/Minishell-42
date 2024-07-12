#include "parser.h"

char	**convert_array(t_env *env)
{
	char	**nenv;
	t_env	*cpy;
	int		size;

	cpy = env;
	size = 0;
	while (cpy)
	{
		size++;
		cpy = cpy->next;
	}
	nenv = malloc((size + 1) * sizeof(char *));
	nenv[size] = NULL;
	size = 0;
	while (env)
	{
		if (env->value)
			nenv[size] = ft_strjoin3elem(env->key, "=", env->value);
		else
			nenv[size] = ft_strdup(env->key);
		size++;
		env = env->next;
	}
	return (nenv);
}

t_env	*init_env_line(char *key, char *value)
{
	t_env	*env_node;

	env_node = malloc(sizeof(t_env));
	env_node->key = key;
	env_node->value = value;
	env_node->next = NULL;
	return (env_node);
}

t_env	*envlast(t_env *lst)
{
	t_env	*last;

	last = NULL;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	add_env_line(t_env **env, t_env *node)
{
	t_env	*elem;

	if (env && node)
	{
		elem = envlast(*env);
		if (!elem)
			*env = node;
		if (elem)
			elem -> next = node;
		node -> next = NULL;
	}
}

void	env_clear(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		free((*env)->key);
		free((*env)->value);
		(*env) = (*env)->next;
		free(tmp);
		tmp = NULL;
	}
}

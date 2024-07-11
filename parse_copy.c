#include "Pipex/inc/pipex_bonus.h"
#include "parser.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

char	**ft_split1(char *str, char c)
{
	char	**split;
	int		i;

	split = ft_split(str, c);
	i = 2;
	if (split[1] == NULL)
		return (split);	
	while (split[i])
	{
		split[1] = add_str(split[1], "=");
		split[1] = add_str(split[1], split[i]);
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	return (split);
}

void	put_env(t_env *my_env, int fd)
{
	if (fd == -1)
		printf("Error opening file: %s\n", strerror(errno));
	while (my_env)
	{
		ft_putstr_fd(my_env->key, fd);
		ft_putstr_fd("=", fd);
		if (my_env->value)
			ft_putendl_fd(my_env->value, fd);
		else
			ft_putstr_fd("\n", fd);
		my_env = my_env->next;
	}
	close(fd);
}

char	*ft_strjoin3elem(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*ret2;

	ret = ft_strjoin(s1, s2);
	if (s3)
		ret2 = ft_strjoin(ret, s3);
	else
		ret2 = ft_strjoin(ret, "");
	free(ret);
	return (ret2);
}

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

char	*ft_strtrim2(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 == '\0' || *set == '\0')
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	ptr = ft_substr(s1, start, (end - start));
	return (ptr);
}

int	abs(int i)
{
	if (i < 0)
		i *= (-1);
	return (i);
}

int	in_env(t_env *env, char *s)
{
	while (env)
	{
		if (ft_strncmp(env->key, s, 2147483647) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	ft_mystrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] && s2[i] != '\0') && (s1[i] == s2[i]) && (i < n - 1))
		i++;
	return (((unsigned char)s1[i] - (unsigned char)s2[i]) + (i + 1));
}

t_env	*order_env(t_env *env)
{
	t_env	*ret;
	char	**array;
	char	*tmp;
	int		i;
	int		j;

	array = convert_array(env);
	i = -1;
	while (array[(++i) + 1] != NULL)
	{
		j = 0;
		while (array[j + 1] != NULL)
		{
			if (ft_strncmp(array[j], array[j + 1], 2147483647) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
	}
	ret = generate_env2(array);
	ft_free(array);
	return (ret);
}
/********************************************************/
/*														*/
/*				is_is_str() doc:						*/
/*		This function compare a character				*/
/*	with a string to find if it is in the string		*/
/*														*/
/********************************************************/

int	is_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	nlstsize(t_nlist *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

void	nlstclear(t_nlist **lst)
{
	t_nlist	*elem;

	if (!lst)
		return ;
	while (*lst)
	{
		elem = *lst;
		*lst = elem->next;
		free(elem);
	}
	free(*lst);
	*lst = NULL;
}

t_nlist	*nlst_new(char c)
{
	t_nlist	*node;

	node = malloc(sizeof(t_nlist));
	node->c = c;
	node->next = NULL;
	return (node);
}

t_nlist	*nstlast(t_nlist *lst)
{
	t_nlist	*last;

	last = NULL;
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}

void	nlstadd_back(t_nlist **lst, t_nlist *new)
{
	t_nlist	*elem;

	if (lst && new)
	{
		elem = nstlast(*lst);
		if (!elem)
			*lst = new;
		if (elem)
			elem -> next = new;
		new -> next = NULL;
	}
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	free(s1);
	s1 = ft_strjoin(ret, " ");
	free(ret);
	return (s1);
}

t_nlist	*create_stack_1(char *str)
{
	t_nlist	*lst;
	int		i;

	lst = NULL;
	i = 0;
	while (str[i])
	{
		nlstadd_back(&lst, nlst_new(str[i]));
		i++;
	}
	return (lst);
}

char	*join_stack(t_nlist *stack)
{
	char	*s;
	int		siz;
	int		i;

	i = 0;
	siz = nlstsize(stack);
	s = ft_calloc(siz + 1, sizeof(char));
	while (i < siz)
	{
		s[i] = stack->c;
		stack = stack->next;
		i++;
	}
	return (s);
}

void	ft_del(void	*content)
{
	free(content);
}

void	create_stack32(t_nlist **stack1, t_nlist **stack2, \
t_list **stack3, char **s)
{
	*s = join_stack(*stack2);
	ft_lstadd_back(stack3, ft_lstnew(ft_strdup(*s)));
	nlstclear(stack2);
	free(*s);
	*s = NULL;
	*stack1 = (*stack1)->next;
}

void	create_stack33(t_nlist **stack1, t_nlist **stack2)
{
	nlstadd_back(stack2, nlst_new((*stack1)->c));
	(*stack1) = (*stack1)->next;
	while ((*stack1)->c != '"')
	{
		nlstadd_back(stack2, nlst_new((*stack1)->c));
		(*stack1) = (*stack1)->next;
	}
	nlstadd_back(stack2, nlst_new((*stack1)->c));
	(*stack1) = (*stack1)->next;
}

void	create_stack34(t_nlist **stack1, t_nlist **stack2)
{
	nlstadd_back(stack2, nlst_new((*stack1)->c));
	(*stack1) = (*stack1)->next;
	while ((*stack1)->c != '\'')
	{
		nlstadd_back(stack2, nlst_new((*stack1)->c));
		(*stack1) = (*stack1)->next;
	}
	nlstadd_back(stack2, nlst_new((*stack1)->c));
	(*stack1) = (*stack1)->next;
}

void	create_stack35(t_nlist **stack1, t_nlist **stack2, \
t_list **stack3, char **s)
{
	if (*stack2 != NULL)
	{
		*s = join_stack(*stack2);
		ft_lstadd_back(stack3, ft_lstnew(ft_strdup(*s)));
		nlstclear(stack2);
		free(*s);
	}
	nlstadd_back(stack2, nlst_new((*stack1)->c));
	*s = join_stack(*stack2);
	ft_lstadd_back(stack3, ft_lstnew(ft_strdup(*s)));
	nlstclear(stack2);
	free(*s);
	*stack1 = (*stack1)->next;
}

void	create_stack36(t_nlist **stack1, t_nlist **stack2)
{
	nlstadd_back(stack2, nlst_new((*stack1)->c));
	(*stack1) = (*stack1)->next;
}

void	create_stack37(t_nlist **stack2, t_list **stack3, char **s)
{
	ft_lstadd_back(stack3, ft_lstnew(ft_strdup(*s)));
	nlstclear(stack2);
	free(*s);
}

t_list	*create_stack3(t_nlist *stack1)
{
	t_nlist	*stack2;
	t_list	*stack3;
	char	*s;

	s = NULL;
	stack2 = NULL;
	stack3 = NULL;
	while (stack1 != NULL)
	{
		if (stack1->c == ' ' && stack2 != NULL)
			create_stack32(&stack1, &stack2, &stack3, &s);
		else if (stack1->c == '"')
			create_stack33(&stack1, &stack2);
		else if (stack1->c == '\'')
			create_stack34(&stack1, &stack2);
		else if (stack1->c == '<' || stack1->c == '>' || stack1->c == '|')
			create_stack35(&stack1, &stack2, &stack3, &s);
		else
			create_stack36(&stack1, &stack2);
	}
	if (stack2 != NULL)
		s = join_stack(stack2);
	if (s != NULL)
		create_stack37(&stack2, &stack3, &s);
	return (stack3);
}

char	*add_str(char *str, char *s)
{
	char	*ret;

	ret = ft_strjoin(str, s);
	free(str);
	return (ret);
}

char	*add_str2(char *str, char **s)
{
	char	*ret;

	ret = ft_strjoin(str, *s);
	free(*s);
	return (ret);
}

void	iq42(t_nlist *stacks[], char *strs[], int flag)
{
	char	*str;

	if (stacks[2] == NULL || stacks[2]->c == ' ')
	{
		//ft_putendl_fd("JJJ", 2);
		if (stacks[2])
			stacks[2] = stacks[2]->next;
		strs[1] = join_stack(stacks[1]);
		nlstclear(&stacks[1]);
		strs[1] = add_str(strs[1], "$");
		strs[0] = add_str(strs[0], strs[1]);
		free(strs[1]);
	}
	else
	{
		stacks[2] = stacks[2]->next;
		strs[1] = join_stack(stacks[1]);
		nlstclear(&stacks[1]);
		str = ft_itoa(flag);
		strs[1] = add_str(strs[1], str);
		free(str);
		strs[0] = add_str(strs[0], strs[1]);
		free(strs[1]);
	}
}

void	iq4(t_nlist *stacks[], char *strs[], int flag, t_env *env)
{
	if (stacks[2]->c == '$')
	{
		stacks[2] = stacks[2]->next;
		if (stacks[2] == NULL || stacks[2]->c == '?' || stacks[2]->c == ' ')
			iq42(stacks, strs, flag);
		else
		{
			while (stacks[2] != NULL && (ft_isalnum(stacks[2]->c) || \
			stacks[2]->c == '_'))
			{
				nlstadd_back(&stacks[1], nlst_new(stacks[2]->c));
				stacks[2] = stacks[2]->next;
			}
			strs[1] = join_stack(stacks[1]);
			nlstclear(&stacks[1]);
			strs[0] = add_str(strs[0], ft_getenv(strs[1], env));
			free(strs[1]);
		}
	}
	else
	{
		strs[2][0] = stacks[2]->c;
		strs[0] = add_str(strs[0], strs[2]);
		stacks[2] = stacks[2]->next;
	}
}

void	iq32(t_nlist *stacks[], char *strs[], int flag, t_env *env)
{
	int	f;

	f = 0;
	stacks[2] = stacks[2]->next;
	if (stacks[2]->c == ' ' || stacks[2]->c == '"')
	{
		//ft_putendl_fd("JJJ", 2);
		strs[1] = join_stack(stacks[1]);
		nlstclear(&stacks[1]);
		strs[1] = add_str(strs[1], "$");
		strs[0] = add_str(strs[0], strs[1]);
		free(strs[1]);
	}
	else if (stacks[2]->c == '?')
	{
		stacks[2] = stacks[2]->next;
		strs[1] = join_stack(stacks[1]);
		nlstclear(&stacks[1]);
		strs[1] = add_str(strs[1], ft_itoa(flag));
		strs[0] = add_str(strs[0], strs[1]);
		free(strs[1]);
	}
	else
	{
		// Créer une fonction 
		if (stacks[2]->c == '\'')
		{
			nlstadd_back(&stacks[1], nlst_new('$'));
			f = 1;
		}
		while (ft_isalnum(stacks[2]->c) || stacks[2]->c == '_')
		{
			nlstadd_back(&stacks[1], nlst_new(stacks[2]->c));
			stacks[2] = stacks[2]->next;
		}
		strs[1] = join_stack(stacks[1]);
		nlstclear(&stacks[1]);
		if (f == 0)
			strs[0] = add_str(strs[0], ft_getenv(strs[1], env));
		else
			strs[0] = add_str(strs[0], strs[1]);
		free(strs[1]);
		// Fin de la fonction
	}
}

void	iq3(t_nlist *stacks[], char *strs[], int flag, t_env *env)
{
	stacks[2] = stacks[2]->next;
	while (stacks[2]->c != '\"')
	{
		if (stacks[2]->c == '$')
			iq32(stacks, strs, flag, env);
		else
		{
			strs[2][0] = stacks[2]->c;
			strs[0] = add_str(strs[0], strs[2]);
			stacks[2] = stacks[2]->next;
		}
	}
	stacks[2] = stacks[2]->next;
}

void	iq2(t_nlist *stacks[], char *strs[])
{
	stacks[2] = stacks[2]->next;
	while (stacks[2]->c != '\'')
	{
		strs[2][0] = stacks[2]->c;
		strs[0] = add_str(strs[0], strs[2]);
		stacks[2] = stacks[2]->next;
	}
	stacks[2] = stacks[2]->next;
}

void	iq12(t_nlist *stacks[], char *strs[], int flag, t_env *env)
{
	if (stacks[2]->c == '\'')
		iq2(stacks, strs);
	else if (stacks[2]->c == '\"')
		iq3(stacks, strs, flag, env);
	else
		iq4(stacks, strs, flag, env);
}

t_list	*interpret_quotes(t_list *lst, int flag, t_env *env)
{
	t_list	*ret;
	t_nlist	*stacks[3];
	char	*strs[3];

	strs[2] = ft_calloc(2, sizeof(char));
	ret = NULL;
	stacks[1] = NULL;
	while (lst)
	{
		strs[0] = ft_calloc(1, sizeof(char));
		stacks[0] = create_stack_1(lst->content);
		stacks[2] = stacks[0];
		while (stacks[2])
			iq12(stacks, strs, flag, env);
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup(strs[0])));
		free(strs[0]);
		nlstclear(&(stacks[0]));
		lst = lst->next;
	}
	free(strs[2]);
	return (ret);
}

char	**gen_args(t_list **lst)
{
	t_list	*cpy;
	int		nb;
	char	**array;

	nb = 0;
	cpy = *lst;
	while (cpy && ((char *)cpy->content)[0] != '>')
	{
		nb++;
		cpy = cpy->next;
	}
	array = ft_calloc(nb + 2, sizeof(char *));
	array[nb + 1] = NULL;
	nb = 0;
	while ((*lst)->next && ((char *)(*lst)->next->content)[0] != '>')
	{
		if (only_in((*lst)->content, ' '))
		{
			nb--;
			(*lst) = (*lst)->next;
		}
		else if (((char *)((*lst)->content))[0] == ' ')
		{
			array[nb] = ft_strtrim2((*lst)->content, " ");
			(*lst) = (*lst)->next;
		}
		else
		{
			array[nb] = ft_substr((*lst)->content, 0, \
					ft_strlen((*lst)->content));
			(*lst) = (*lst)->next;
		}
		nb++;
	}
	if (((char *)((*lst)->content))[0] == ' ')
		array[nb] = ft_strtrim2((*lst)->content, " ");
	else
		array[nb] = ft_substr((*lst)->content, 0, ft_strlen((*lst)->content));
	return (array);
}

char	**find_all_path(char **var_env)
{
	int		i;
	char	**t1;
	char	**t2;

	i = 0;
	while (var_env[i] != NULL)
	{
		if (ft_strncmp("PATH", var_env[i], 4) == 0)
		{
			t1 = ft_split(var_env[i], '=');
			t2 = ft_split(t1[1], ':');
			ft_free(t1);
			return (t2);
		}
		i++;
	}
	return (NULL);
}

char	*find_nice_path(char *cmd, char **env)
{
	char	**split_cmd;
	char	*poss_path1;
	char	*poss_path2;
	int		i;
	char	**path;

	path = find_all_path(env);
	if (path == NULL)
		return (NULL);
	i = -1;
	split_cmd = ft_split(cmd, ' ');
	while (path[++i] != NULL)
	{
		poss_path1 = ft_strjoin(path[i], "/");
		if (split_cmd[0] == NULL)
			poss_path2 = ft_strjoin(poss_path1, "noexist");
		else
			poss_path2 = ft_strjoin(poss_path1, split_cmd[0]);
		if (access(poss_path2, F_OK) == 0)
		{
			ft_free(split_cmd);
			return (free(poss_path1), ft_free(path), poss_path2);
		}
		free(poss_path1);
		free(poss_path2);
	}
	ft_free(split_cmd);
	return (ft_free(path), NULL);
}

int	only_in(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}

int	only_in2(char *str, char c, char c2)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != c && str[i] != c2)
			return (0);
	}
	return (1);
}

t_cmd	handle_hdoc(t_list **l, t_env *menv)
{
	t_cmd	cmd;
	char	**env;

	env = convert_array(menv);
	if (is_in_str('/', (*l)->content) == 0)
		cmd.path = find_nice_path((*l)->content, env);
	else
	{
		if (((char *)((*l)->content))[0] == ' ')
			cmd.path = ft_strtrim2((*l)->content, " ");
		else
			cmd.path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
	}
	*l = (*l)->next;
	//ft_putendl_fd((*l)->content, 2);
	cmd.args = gen_args(l);
	cmd.type = HDOC;
	ft_free(env);
	return (cmd);
}

t_cmd	handle_hdoc2(t_list **l, t_env *menv)
{
	t_cmd	cmd;
	char	**env;

	env = convert_array(menv);
	if (is_in_str('/', (*l)->content) == 0)
		cmd.path = find_nice_path((*l)->next->next->content, env);
	else
	{
		if (((char *)((*l)->content))[0] == ' ')
			cmd.path = ft_strtrim2((*l)->next->next->content, " ");
		else
			cmd.path = ft_substr((*l)->next->next->content, \
					0, ft_strlen((*l)->next->next->content));
	}
	//ft_putendl_fd((*l)->content, 2);
	cmd.args = gen_args(l);
	free(cmd.args[2]);
	cmd.args[2] = NULL;
	cmd.type = HDOC;
	ft_free(env);
	return (cmd);
}

void	ca23(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i + 1].path = ft_strtrim2((*l)->content, " ");
	else
		(*cmd_array)[*i + 1].path = ft_substr((*l)->content, 0, \
				ft_strlen((*l)->content));
}

void	ca22(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i].path = ft_strtrim2((*l)->content, " ");
	else
		(*cmd_array)[*i].path = ft_substr((*l)->content, 0, \
				ft_strlen((*l)->content));
}

int	detect_builtin(char *str)
{
	if (ft_strncmp("cd", str, 2147483647) == 0 || \
	ft_strncmp("echo", str, 2147483647) == 0 || \
	ft_strncmp("pwd", str, 2147483647) == 0 || \
	ft_strncmp("unset", str, 2147483647) == 0 || \
	ft_strncmp("export", str, 2147483647) == 0 || \
	ft_strncmp("env", str, 2147483647) == 0)
		return (0);
	return (1);
}

void	ca2(t_list **l, int *i, t_cmd **cmd_array, t_env *env)
{
	int		flag;
	char	**nenv;
	char	*s;

	flag = 0;
	while (((char *)((*l)->content))[0] == '<')
	{
		(*l) = (*l)->next;
		//ft_putendl_fd(((char *)((*l)->content)), 2);
		ca22(l, i, cmd_array);
		(*cmd_array)[*i].args = NULL;
		(*cmd_array)[*i].type = RED_IN;
		(*l) = (*l)->next;
		(*i)++;
	}
	(*i)--;
	if (((char *)((*l)->content))[0] == ';')
	{
		//ft_putendl_fd("HDOC Here", 2);
		(*cmd_array)[*i + 1] = handle_hdoc2(l, env);
	}
	else if (((char *)((*l)->next->content))[0] == ';')
	{
		//ft_putendl_fd("HDOC Here", 2);
		(*cmd_array)[*i + 1] = handle_hdoc(l, env);
	}
	else
	{
		if (is_in_str('/', (*l)->content) == 0)
		{
			//ft_putendl_fd((*l)->content, 2);
			s = ft_strtrim2((*l)->content, " ");
			if (detect_builtin(s) == 0)
			{
				free(s);
				flag = 1;
				(*cmd_array)[*i + 1].path = ft_strdup((*l)->content);
			}
			else
			{
				free(s);
				nenv = convert_array(env);
				(*cmd_array)[*i + 1].path = find_nice_path((*l)->content, nenv);
				ft_free(nenv);
			}
		}
		else
			ca23(l, i, cmd_array);
		if ((*cmd_array)[*i + 1].path == NULL)
		{
			(*cmd_array)[*i + 1].path = ft_strdup((*l)->content);
			(*cmd_array)[*i + 1].args = NULL;
			(*cmd_array)[*i + 1].type = NONE;
			ft_free(gen_args(l));
		}
		else
		{
			(*cmd_array)[*i + 1].args = gen_args(l);
			if (flag == 1)
				(*cmd_array)[*i + 1].type = BUILTIN;
			else
				(*cmd_array)[*i + 1].type = CMD;
		}
	}
}

void	ca32(t_list **l, int *i, t_cmd **cmd_array, int *j)
{
	free((*cmd_array)[*i + *j].path);
	(*cmd_array)[*i + *j].path = ft_strtrim2((*l)->content, " ");
}

int	ca3(t_list **l, int tab[], t_cmd **cmd_array)
{
	int	f;

	f = 0;
	while (((char *)((*l)->content))[0] != '>')
		*l = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] == '>' && (*l)->next)
	{
		if (((char *)((*l)->content))[0] == '>')
			(*l) = (*l)->next;
		if (((char *)((*l)->content))[0] == '>')
		{
			f = 1;
			(*l) = (*l)->next;
		}
		ca32(l, &(tab[0]), cmd_array, &(tab[1]));
		(*cmd_array)[tab[0] + tab[1]].args = NULL;
		if (f == 1)
			(*cmd_array)[tab[0] + tab[1]].type = RED_APP;
		else
			(*cmd_array)[tab[0] + tab[1]].type = RED_OUT;
	}
	if (ft_strlen((*cmd_array)[tab[0] + tab[1]].path) != 0)
		(tab[1])++;
	return (0);
}

t_cmd	*create_args(t_list *l, t_env *env)
{
	t_cmd	*cmd_array;
	int		tab[2];

	tab[0] = 0;
	tab[1] = 2;
	cmd_array = ft_calloc(ft_lstsize(l) - 1, sizeof(t_cmd));
	while (l)
	{
		//ft_putendl_fd(l->content, 2);
		ca2(&l, &(tab[0]), &cmd_array, env);
		while (l->next && ((char *)(l->next->content))[0] != '<')
		{
			//ft_putstr_fd("VALUE :", 2);
			//ft_putendl_fd(l->content, 2);
			ca3(&l, tab, &cmd_array);
		}
		if (l)
		{
			//ft_putstr_fd("VAL: ", 2);
			//ft_putendl_fd(((char *)(l->content)), 2);
		}
		if (l)
			l = l->next;
		tab[0] += tab[1];
		tab[1] = 2;
	}
	
	cmd_array[tab[0]].type = END;
	tab[0] = 0;
	while (cmd_array[tab[0]].type != END)
	{
		ft_putstr_fd(cmd_array[tab[0]].path, 2);
		tab[1] = -1;
		ft_putchar_fd('\\', 2);
		while (cmd_array[tab[0]].args && cmd_array[tab[0]].args[++(tab[1])])
		{
			ft_putstr_fd(cmd_array[tab[0]].args[tab[1]], 2);
			ft_putchar_fd('/', 2);
		}
		ft_putnbr_fd(cmd_array[tab[0]].type, 2);
		ft_putchar_fd('\n', 2);
		(tab[0])++;
	}
	return (cmd_array);
}

void	do1cmd2(int fd[], int *i, t_cmd *cmds)
{
	if (fd[1] != -1)
		close(fd[1]);
	if (cmds[*i].type == RED_OUT)
		fd[1] = open(cmds[*i].path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd[1] = open(cmds[*i].path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	(*i)++;
}

void	clear_cmds(t_cmd *cmds)
{
	int	j;

	j = 0;
	while (cmds[j].type != END)
	{
		free(cmds[j].path);
		if (cmds[j].args)
		{
			//ft_putendl_fd(cmds[j].args[0], 2);
			ft_free(cmds[j].args);
		}
		j++;
	}
	free(cmds);
}

void	handle_sigint2(int sig)
{
	(void)sig;

	//ft_putendl_fd("EXIT CTRL+C", 2);
	exit(1);
}

int	do1cmd(t_cmd *cmds, char **env, t_cmd *cmd)
{
	int		fd[2];
	int		i;
	int		j;

	signal(SIGINT, handle_sigint2);
	i = 0;
	//ft_putendl_fd("AA", 2);
	//ft_putendl_fd("AB", 2);
	fd[0] = open("/dev/stdin", O_RDONLY);
	while (cmds[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmds[i - 1].path, 2);
			ft_putendl_fd(": No suchhh file or directory", 2);
			exit(127);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmds[i].path, O_RDONLY);
		i++;
	}
	j = i;
	i++;
	if (cmds[i - 1].type == NONE)
	{
		if (ft_strncmp(cmds[i - 1].path, "", 2147483647) == 0)
		{
			clear_cmds(cmd);
			free(cmds);
			ft_free(env);
			close(fd[0]);
			exit(0);
		}
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmds[i - 1].path, 2);
		ft_putendl_fd(": command not found", 2);
		clear_cmds(cmd);
		free(cmds);
		ft_free(env);
		close(fd[0]);
		exit(127);
	}
	if (access(cmds[j].path, F_OK) != 0)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[j].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), \
		free(cmds), clear_cmds(cmd), ft_free(env), exit(127), 0);
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[i - 2].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), \
		free(cmds), clear_cmds(cmd), ft_free(env), exit(127), 0);
	dup2(fd[0], 0);
	close(fd[0]);
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmds[i].type != END)
		do1cmd2(fd, &i, cmds);
	if (fd[1] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[i - 1].path, 2), \
		ft_putendl_fd(": No such file or directory", 2), \
		free(cmds), clear_cmds(cmd), ft_free(env), exit(127), 0);
	dup2(fd[1], 1);
	close(fd[1]);
	if (execve(cmds[j].path, cmds[j].args, env))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmds[j].path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(cmds);
		clear_cmds(cmd);
		ft_free(env);
	}
	exit(126);
}

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

int	bltin_cd(t_cmd cmd, t_env *env)
{
	if (count_size_args(cmd.args) > 2)
	{
		ft_putendl_fd("bash : cd : too many args", 2);
		return (1);
	}
	if (count_size_args(cmd.args) == 1)
	{
		chdir(ft_getenv("HOME", env));
		return (0);
	}
	if (access(cmd.args[1], F_OK) == -1)
	{
		ft_putstr_fd("bash : cd : ", 2);
		ft_putstr_fd(cmd.args[1], 2);
		ft_putendl_fd(" : No such file or directory", 2);
		return (1);
	}
	//ft_putendl_fd("Almost Done", 2);
	if (chdir(cmd.args[1]) != 0)
	{
		perror("chdir ");
		return (1);
	}
	//ft_putendl_fd("Done", 2);
	return (0);
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
		{
			//ft_putendl_fd("UUUUUU", 2);
			add_env_line(&cpy, init_env_line(ft_strdup((cp)->key), s));
		}
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

int	builtin_cd_prep(t_cmd *cmd, t_env **env)
{
	int		fd[2];
	int		i;
	int		j;
	int		k;
	char	*str[2];
	char	cwd[1024];

	i = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (127);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
		i++;
	}
	if (fd[0] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd[i - 1].path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	j = i;
	i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	str[0] = ft_getenv("PWD", *env);
	k = bltin_cd(cmd[j], *env);
	getcwd(cwd, 1024);
	printf("%s\n%s\n", str[0], cwd);
	(*env) = change_env(ft_strdup(str[0]), env, "OLDPWD");
	(*env) = change_env(ft_strdup(cwd), env, "PWD");
	close(fd[0]);
	close(fd[1]);
	return (k);
}

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
		{
			//ft_putstr_fd("need more args\n", 2);
			return ;
		}
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

	i = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
		i++;
	}
	if (fd[0] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd[i - 1].path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	j = i;
	i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	if (count_size_args(cmd[j].args) == 1)
	{
		ft_putstr_fd("\n", fd[1]);
		return (0);
	}
	bltin_echo(cmd[j], fd[1]);
	close(fd[1]);
	close(fd[0]);
	return (0);
}

int	bltin_pwd(int fd)
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = calloc(size, sizeof(char *));
	if (!buffer)
		return (1);
	while (getcwd(buffer, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size *= 2;
			free(buffer);
			buffer = calloc(size, sizeof(char *));
			if (!buffer)
				return (1);
		}
		else
		{
			free(buffer);
			return (1);
		}
	}
	ft_putendl_fd(buffer, fd);
	free(buffer);
	return (0);
}

int	builtin_pwd_prep(t_cmd *cmd)
{
	int	i;
	int	j;
	int	k;
	int	fd[2];

	i = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
		i++;
	}
	if (fd[0] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd[i - 1].path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	j = i;
	i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	/*if (count_size_args(cmd[j].args) > 1)
	{
		ft_putstr_fd("Too many args\n", 2);
		return (0);
	}*/
	k = bltin_pwd(fd[1]);
	close(fd[1]);
	close(fd[0]);
	return (k);
}

int	bltin_unset(t_cmd cmd, t_env **env)
{
	int		i;
	t_env	*cp;
	t_env	*to_clear;

	i = 1;
	while (cmd.args[i])
	{
		cp = *env;
		while (cp)
		{
			if (cp->next && ft_strncmp(cp->next->key, cmd.args[i], \
			2147483647) == 0)
			{
				to_clear = cp->next;
				cp->next = cp->next->next;
				free(to_clear->key);
				free(to_clear->value);
				free(to_clear);
			}
			else if (cp->next == NULL && \
			ft_strncmp(cp->key, cmd.args[i], 2147483647) == 0)
			{
				free(cp->key);
				free(cp->value);
				free(cp);
				cp = NULL;
			}
			cp = cp->next;
		}
		i++;
	}
	return (0);
}

int	builtin_unset_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	j;
	int	k;
	int	fd[2];

	i = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
		i++;
	}
	if (fd[0] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd[i - 1].path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	j = i;
	i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	k = bltin_unset(cmd[j], env);
	close(fd[1]);
	close(fd[0]);
	return (k);
}

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
	int	i;
	int	j;
	int	k;
	int	fd[2];

	i = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
		i++;
	}
	if (fd[0] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd[i - 1].path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	j = i;
	i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	if (count_size_args(cmd[j].args) > 1)
	{
		//ft_putstr_fd("Too many args\n", 2);
		return (1);
	}
	k = bltin_env(*env, fd[1]);
	close(fd[1]);
	close(fd[0]);
	return (k);
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
void	bltin_export2(t_cmd cmd, t_env **env, int size)
{
	int		n;
	char	**split;
	t_env	**cp;

	cp = env;
	n = 1;
	while (n < size)
	{
		if (is_in_str('=', cmd.args[n]))
		{
			split = ft_split1(cmd.args[n], '=');
			remove_env(env, split[0]);
			if (split[1])
				add_env_line(env, init_env_line(ft_strdup(split[0]),\
				ft_strdup(split[1])));
			else
				add_env_line(env, init_env_line(ft_strdup(split[0]), \
				NULL));
			ft_free(split);
		}
		else
			add_env_line(env, init_env_line(ft_strdup(cmd.args[n]), NULL));
		n++;
	}
}

int	bltin_export(t_cmd cmd, t_env **env, int fd)
{
	int		size[2];
	t_env	*cp;
	t_env	*cpy;

	size[0] = count_size_args(cmd.args);
	cp = order_env(*env);
	cpy = cp;
	if (size[0] == 1)
	{
		while (cp)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(cp->key, fd);
			if (cp->value)
			{
				ft_putstr_fd("=\"", fd);
				if (ft_strncmp(cp->key, "_", 2) == 0)
					ft_putstr_fd("/usr/bin/env", fd);
				else
					ft_putstr_fd(cp->value, fd);
				ft_putstr_fd("\"\n", fd);
			}
			else
				ft_putstr_fd("\n", fd);
			cp = cp->next;
		}
	}
	else 
		bltin_export2(cmd, env, size[0]);
	env_clear(&cpy);
	return (0);
}

int	builtin_export_prep(t_cmd *cmd, t_env **env)
{
	int	i;
	int	j;
	int	k;
	int	fd[2];

	i = 0;
	fd[0] = open("/dev/stdout", O_WRONLY);
	while (cmd[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (1);
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmd[i].path, O_RDONLY);
		i++;
	}
	if (fd[0] == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd[i - 1].path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	j = i;
	i++;
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	k = bltin_export(cmd[j], env, fd[1]);
	close(fd[1]);
	close(fd[0]);
	return (k);
}

int	find_hdoc2(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].type != END)
	{
		if (cmd[i].type == HDOC)
			return (1);
		i++;
	}
	return (0);
}

int	simulpipe(t_cmd *cmd, t_env **env)
{
	int		status;
	int		tab[6];
	int		*j;
	int		i;
	t_cmd	*type;
	pid_t	pid;
	char	**nenv;

	status = 0;
	tab[4] = 0;
	tab[5] = find_hdoc2(cmd);
	i = -1;
	j = find_hdocs(cmd, 0);
	sim_glob('v', NULL, NULL, j);
	while (j[++i] != -1)
		handle_hdocs((cmd[j[i]].args)[1], cmd, j[i], env);
	/*if (((int *)sim_glob('n', NULL, NULL, NULL))[0] != -10)
	{
		sim_glob('h', NULL, NULL, NULL);
		ft_putendl_fd("....", 2);
		exit(0);
	}*/
	free(j);
	tab[0] = 0;
	if ((cmd)[tab[0]].type == ENDT)
	{
		clear_cmds(cmd);
		ft_free(sim_glob('o', NULL, NULL, NULL));
		env_clear(env);
		exit(status);
	}
	while ((cmd)[tab[0]].type != END)
	{
		if ((cmd)[tab[0] + 1].type == HDOC)
			return (clear_cmds(cmd), env_clear(env), status);
		tab[2] = tab[0];
		tab[1] = 0;
		simulpipe2(tab, cmd, &type);
		tab[3] = 0;
		while (type[tab[3]].type == RED_IN)
			tab[3]++;
		if (type[tab[3]].type == BUILTIN)
		{
			tab[4] = 1;
			if (ft_strncmp(type[tab[3]].path, "cd", 2147483647) == 0)
				status = builtin_cd_prep(type, env);
			else if (ft_strncmp(type[tab[3]].path, "echo", 2147483647) == 0)
				status = builtin_echo_prep(type);
			else if (ft_strncmp(type[tab[3]].path, "pwd", 2147483647) == 0)
				status = builtin_pwd_prep(type);
			else if (ft_strncmp(type[tab[3]].path, "unset", 2147483647) == 0)
				status = builtin_unset_prep(type, env);
			else if (ft_strncmp(type[tab[3]].path, "env", 2147483647) == 0)
				status = builtin_env_prep(type, env);
			else if (ft_strncmp(type[tab[3]].path, "export", 2147483647) == 0)
				status = builtin_export_prep(type, env);
			free(type);
		}
		else
		{
			tab[4] = 0;
			nenv = convert_array(*env);
			pid = fork();
			if (pid == 0)
			{
				env_clear(env);
				do1cmd(type, nenv, cmd);
			}
			else
			{
				waitpid(pid, &status, 0);
				free(type);
				ft_free(nenv);
			}
		}
	}
	tab[0] = 0;
	//ft_putendl_fd("---___---", 2);
	while (cmd[tab[0]].type != END)
	{
		free(cmd[tab[0]].path);
		if (cmd[tab[0]].args)
		{
			//ft_putendl_fd(cmd[tab[0]].args[0], 2);
			ft_free(cmd[tab[0]].args);
		}
		(tab[0])++;
	}
	free(cmd);
	//ft_putendl_fd("___---___", 2);
	if (tab[5] == 1)
	{
		env_clear(env);
		if (tab[4] == 1)
			exit(status); //return (status);
		else
			exit(WEXITSTATUS(status)); //return (WEXITSTATUS(status));
	}
	else
	{
		if (tab[4] == 1)
			return (status);
		else
			return (WEXITSTATUS(status));
	}
}

void	apply_flags(t_list *t_lst, int flags[])
{
	if (t_lst == NULL)
	{
		//ft_putendl_fd("....", 2);
		exit(1);
	}
	while (t_lst)
	{
		if (((char *)t_lst->content)[0] == '<')
			flags[0] = 1;
		else if (t_lst->next && ((char *)t_lst->content)[0] == '>' && \
		((char *)t_lst->next->content)[0] == '>')
		{
			flags[1] = 1;
			t_lst = t_lst->next;
		}
		else if (((char *)t_lst->content)[0] == '>')
			flags[2] = 1;
		else if (((char *)t_lst->content)[0] == '|')
			flags[3] = 1;
		t_lst = t_lst->next;
	}
}

t_list	*lstdup(t_list *lst)
{
	t_list	*new_lst;

	new_lst = NULL;
	while (lst)
	{
		ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(lst->content)));
		lst = lst->next;
	}
	return (new_lst);
}

t_list	*change_lst(t_list **lst)
{
	t_list	*new_lst;
	t_list	*tmp_lst;
	t_list	*tmp;
	t_list	*cpy;
	char	*str;

	tmp = NULL;
	cpy = *lst;
	while (cpy)
	{
		if (((char *)cpy->content)[0] == '<' && \
				((char *)cpy->next->content)[0] == '<')
		{
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(";")));
			cpy = cpy->next;
		}
		else
			ft_lstadd_back(&tmp, ft_lstnew(ft_strdup(cpy->content)));
		cpy = cpy->next;
	}
	cpy = tmp;
	new_lst = NULL;
	tmp_lst = NULL;
	str = cpy->next->content;
	cpy = cpy->next->next;
	while (cpy)
	{
		if (((char *)cpy->content)[0] == '<')
		{
			ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup("<")));
			ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(cpy->next->content)));
			cpy = cpy->next;
		}
		else if (((char *)cpy->content)[0] == '|')
		{
			if (new_lst == NULL)
				new_lst = lstdup(tmp_lst);
			else
				ft_lstlast(new_lst)->next = lstdup(tmp_lst);
			ft_lstclear(&tmp_lst, &ft_del);
			tmp_lst = NULL;
		}
		else
			ft_lstadd_back(&tmp_lst, ft_lstnew(ft_strdup(cpy->content)));
		cpy = cpy->next;
	}
	if (new_lst == NULL)
		new_lst = lstdup(tmp_lst);
	else
		ft_lstlast(new_lst)->next = lstdup(tmp_lst);
	ft_lstadd_front(&new_lst, ft_lstnew(ft_strdup(str)));
	ft_lstadd_front(&new_lst, ft_lstnew(ft_strdup("<")));
	ft_lstclear(&tmp_lst, &ft_del);
	ft_lstclear(&tmp, &ft_del);
	return (new_lst);
}

void	main2(char *str, t_env **env, int *flag, int fd)
{
	t_nlist		*lst;
	t_list		*t_lst[3];
	int			flags[6];
	char		**tab;
	static char	*tempfilein[2] = {"< /tmp/tempfile ", "< /tmp/tempfile2 "};
	static char	*tempfileout[2] = {"> /tmp/tempfile ", "> /tmp/tempfile2 "};
	t_cmd		*cmds;

	fd = open("/tmp/tempfile", O_RDWR | O_CREAT, 0644);
	close(fd);
	fd = open("/tmp/tempfile2", O_RDWR | O_CREAT, 0644);
	close(fd);
	flags[4] = 0;
	tab = ft_split(str, '|');
	tab[flags[4]] = add_str2("< /dev/stdin ", &(tab[flags[4]]));
	while (tab[flags[4]] != NULL)
	{
		if (tab[flags[4]][0] != '<')
		{
			if (flags[4] == 0)
				tab[flags[4]] = add_str2("< /dev/stdin ", \
						&(tab[flags[4]]));
			else
			{
				ft_putendl_fd(tab[0], 2);
				if (ft_strchr(tab[0], '"') == NULL) //(ft_strnstr(tab[0], "echo", 2147483647) == NULL)
					tab[flags[4]] = add_str2(tempfilein[(flags[4] + 1) % 2], &(tab[flags[4]]));
			}
		}
		if (is_in_str('>', tab[flags[4]]) == 0)
		{
			if (tab[flags[4] + 1])
			{
				if  (ft_strchr(tab[0], '"') == NULL) //(ft_strnstr(tab[0], "echo", 2147483647) == NULL)
					tab[flags[4]] = add_str(tab[flags[4]], tempfileout[flags[4] % 2]);
			}
			else
				tab[flags[4]] = add_str(tab[flags[4]], "> /dev/stdout");
		}
		flags[4] += 1;
	}
	flags[4] = 1;
	str = ft_strdup(tab[0]);
	free(tab[0]);
	while (tab[flags[4]] != NULL)
	{
		str = add_str(str, "|");
		str = add_str(str, tab[flags[4]]);
		free(tab[flags[4]]);
		flags[4] += 1;
	}
	flags[4] = 0;
	while (++(flags[4]) < 4)
		flags[flags[4]] = 0;
	lst = create_stack_1(str);
	t_lst[0] = create_stack3(lst);
	t_lst[2] = change_lst(&(t_lst[0]));
	t_lst[1] = interpret_quotes(t_lst[2], *flag, *env);
	ft_lstclear(&(t_lst[0]), &ft_del);
	ft_lstclear(&(t_lst[2]), &ft_del);
	nlstclear(&lst);
	//ft_putendl_fd(str, 2);
	free(tab);
	free(str);
	t_lst[0] = t_lst[1];
	apply_flags(t_lst[0], flags);
	cmds = create_args(t_lst[1], *env);
	ft_lstclear(&(t_lst[1]), &ft_del);
	*flag = simulpipe(cmds, env);
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("\n[Minishell] > ", 1);
	return ;
}

int	main(int c, char **v, char **env)
{
	int		flag;
	int		fd;
	char	*str;
	t_env	*my_env;
	char	**t;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	(void)c; // A changer pour la gestion d'erreur
	(void)v; // A changer pour la gestion d'erreur
	my_env = generate_env(env);
	my_env = change_env(ft_itoa(ft_atoi(ft_getenv("SHLVL", my_env)) + 1), &my_env, "SHLVL");
	flag = 0;
	while (1)
	{
		//signal(SIGINT, SIG_IGN);
		str = readline("[Minishell] > ");
		if (!str)
		{
			free(str);
			rl_clear_history();
			env_clear(&my_env);
			exit(0);
		}
		if (str && str[0] != '\0')
			add_history(str);
		t = ft_split(str, ' ');
		if (t[0] && ft_strncmp(t[0], "exit", 5) == 0)
		{
			if (t[1] && t[2])
			{
				ft_putendl_fd("bash: exit: too many args", 2);
				continue ;
			}
			if (t[1])
				flag = ft_atoi(t[1]);
			ft_free(t);
			free(str);
			rl_clear_history();
			env_clear(&my_env);
			exit(flag);
		}
		ft_free(t);
		if (only_in2(str, ' ', '	') == 1)
			continue ; 
		else
		{
			fd = -1;
			main2(str, &my_env, &flag, fd);
			unlink("/tmp/tempfile");
			unlink("/tmp/tempfile2");
			free(str);
		}
	}
	return (1);
}

//L31
//

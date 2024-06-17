#include "Pipex/libft/libft.h"
#include "parser.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/****************************************************/
/*													*/
/*			   is_is_str() doc:						*/
/*	  This function compare a character				*/
/*  with a string to find if it is in the string	*/
/*													*/
/****************************************************/

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

char	*add_str2(char *str, char *s)
{
	char	*ret;

	ret = ft_strjoin(str, s);
	free(s);
	return (ret);
}

void	iq42(t_nlist *stacks[], char *strs[], int flag)
{
	stacks[2] = stacks[2]->next;
	strs[1] = join_stack(stacks[1]);
	nlstclear(&stacks[1]);
	strs[1] = add_str(strs[1], ft_itoa(flag));
	strs[0] = add_str(strs[0], strs[1]);
	free(strs[1]);
}

void	iq4(t_nlist *stacks[], char *strs[], int flag)
{
	if (stacks[2]->c == '$')
	{
		stacks[2] = stacks[2]->next;
		if (stacks[2]->c == '?')
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
			strs[0] = add_str(strs[0], getenv(strs[1]));
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

void	iq32(t_nlist *stacks[], char *strs[], int flag)
{
	stacks[2] = stacks[2]->next;
	if (stacks[2]->c == '?')
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
		while (ft_isalnum(stacks[2]->c) || stacks[2]->c == '_')
		{
			nlstadd_back(&stacks[1], nlst_new(stacks[2]->c));
			stacks[2] = stacks[2]->next;
		}
		strs[1] = join_stack(stacks[1]);
		nlstclear(&stacks[1]);
		strs[0] = add_str(strs[0], getenv(strs[1]));
		free(strs[1]);
	}
}

void	iq3(t_nlist *stacks[], char *strs[], int flag)
{
	stacks[2] = stacks[2]->next;
	while (stacks[2]->c != '\"')
	{
		if (stacks[2]->c == '$')
			iq32(stacks, strs, flag);
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

void	iq12(t_nlist *stacks[], char *strs[], int flag)
{
	if (stacks[2]->c == '\'')
		iq2(stacks, strs);
	else if (stacks[2]->c == '\"')
		iq3(stacks, strs, flag);
	else
		iq4(stacks, strs, flag);
}

t_list	*interpret_quotes(t_list *lst, int flag)
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
			iq12(stacks, strs, flag);
		ft_lstadd_back(&ret, ft_lstnew(ft_strdup(strs[0])));
		free(strs[0]);
		nlstclear(&(stacks[0]));
		lst = lst->next;
	}
	free(strs[2]);
	return (ret);
}

int	find_nb(t_list *lst, char c)
{
	int	n;

	n = 0;
	while (lst)
	{
		if (((char *)lst->content)[0] == '|')
			n++;
		lst = lst->next;
	}
	return (n);
}

char	**gen_args(t_list *lst)
{
	t_list	*cpy;
	int		nb;
	char	**array;

	nb = 0;
	cpy = lst;
	while (((char *)cpy->content)[0] != '|' && ((char *)cpy->content)[0] != '>')
	{
		nb++;
		cpy = cpy->next;
	}
	array = ft_calloc(nb + 2, sizeof(char *));
	array[nb + 1] = NULL;
	nb = 0;
	while (((char *)lst->content)[0] != '|' && ((char *)lst->content)[0] != '>')
	{
		array[nb] = ft_strdup(lst->content);
		lst = lst->next;
		nb++;
	}
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

t_cmd	*create_args(t_list *l, int i, char **env)
{
	t_cmd	*comand_array;

	comand_array = ft_calloc(find_nb(l, '|') + 3, sizeof(t_cmd));
	comand_array[0].path = ft_strtrim(l->next->content, " ");
	comand_array[0].args = NULL;
	l = l->next->next;
	while (((char *)l->content)[0] != '>')
	{
		if (is_in_str('/', l->content))
			comand_array[i].path = ft_strdup(l->content);
		else
			comand_array[i].path = find_nice_path(l->content, env);
		comand_array[i].args = gen_args(l);
		while (((char *)l->content)[0] != '>' && ((char *)l->content)[0] != '|')
			l = l->next;
		if (((char *)l->content)[0] != '>')
			l = l->next;
		i++;
	}
	if (((char *)l->next->content)[0] == '>')
		l = l->next;
	comand_array[i].path = ft_strtrim(l->next->content, " ");
	comand_array[i].args = NULL;
	return (comand_array);
}

int	do1cmd(t_cmd *cmds, int flag, char **env)
{
	int	fd[2];

	if (access(cmds[0].path, F_OK | R_OK) == -1)
		exit(1);
	fd[0] = open(cmds[0].path, O_RDONLY);
	if (fd[0] == -1)
		exit(1);
	dup2(fd[0], 0);
	close(fd[0]);
	if (flag == 0)
		fd[1] = open(cmds[2].path, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd[1] = open(cmds[2].path, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd[1] == -1)
		exit(1);
	dup2(fd[1], 1);
	close(fd[1]);
	execve(cmds[1].path, cmds[1].args, env);
	exit(1);
}

void	apply_flags(t_list *t_lst, int flags[])
{
	while (t_lst)
	{
		if (((char *)t_lst->content)[0] == '<')
			flags[0] = 1;
		else if (((char *)t_lst->content)[0] == '>' && \
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

void	main3(t_list *t_lst[], int flags[], char **env)
{
	t_cmd	*cmds;

	t_lst[0] = t_lst[1];
	apply_flags(t_lst[0], flags);
	if (flags[0] == 0)
	{
		ft_lstadd_front(&t_lst[1], ft_lstnew(ft_strdup("/dev/stdin")));
		ft_lstadd_front(&t_lst[1], ft_lstnew(ft_strdup("<")));
	}
	if (flags[1] == 0 && flags[2] == 0)
	{
		ft_lstadd_back(&t_lst[1], ft_lstnew(ft_strdup(">")));
		ft_lstadd_back(&t_lst[1], ft_lstnew(ft_strdup("/dev/stdout")));
	}
	t_lst[0] = t_lst[1];
	cmds = create_args(t_lst[1], 1, env);
	ft_lstclear(&t_lst[1], &ft_del);
	if (flags[3] == 0)
		do1cmd(cmds, flags[1], env);
}

void	main2(char *str, char **env, int *flag)
{
	t_nlist	*lst;
	t_list	*t_lst[2];
	int		flags[6];
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		flags[4] = -1;
		while (++(flags[4]) < 4)
			flags[flags[4]] = 0;
		lst = create_stack_1(str);
		t_lst[0] = create_stack3(lst);
		t_lst[1] = interpret_quotes(t_lst[0], *flag);
		ft_lstclear(&(t_lst[0]), &ft_del);
		nlstclear(&lst);
		main3(t_lst, flags, env);
	}
	else
	{
		waitpid(pid, &(flags[5]), 0);
		*flag = WEXITSTATUS(flags[5]);
	}
}

int	main(int c, char **v, char **env)
{
	int		flag;
	char	*str;

	flag = -1;
	while (1)
	{
		str = readline(">> ");
		main2(str, env, &flag);
	}
}

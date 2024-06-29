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
	//ft_putendl_fd("HHHHH", 2);
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
	char *str;

	if (stacks[2] == NULL || stacks[2]->c == ' ')
	{
		ft_putendl_fd("JJJ", 2);
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

void	iq4(t_nlist *stacks[], char *strs[], int flag)
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
	if (stacks[2]->c == ' ' || stacks[2]->c == '"')
	{
		ft_putendl_fd("JJJ", 2);
		//stacks[2] = stacks[2]->next;
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

char	**gen_args(t_list **lst)
{
	t_list	*cpy;
	int		nb;
	char	**array;

	nb = 0;
	cpy = *lst;
	while (((char *)cpy->content)[0] != '>')
	{
		nb++;
		cpy = cpy->next;
	}
	array = ft_calloc(nb + 2, sizeof(char *));
	array[nb + 1] = NULL;
	nb = 0;
	while (((char *)(*lst)->next->content)[0] != '>')
	{
		if (((char *)((*lst)->content))[0] == ' ')
			array[nb] = ft_strtrim2((*lst)->content, " ");
		else
			array[nb] = ft_substr((*lst)->content, 0, ft_strlen((*lst)->content));
		(*lst) = (*lst)->next;
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

t_cmd	handle_hdoc(t_list **l, char **env)
{
	t_cmd	cmd;

	if (is_in_str('/', (*l)->content) == 0)
		cmd.path = find_nice_path((*l)->content, env);
	else
	{
		if (((char *)((*l)->content))[0] == ' ')
			cmd.path = ft_strtrim2((*l)->content, " ");
		else
			cmd.path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
	}
	*l = (*l)->next->next->next;
	ft_putendl_fd((*l)->content, 2);
	cmd.args = gen_args(l);
	cmd.type = HDOC;
	return (cmd);
}

void	ca23(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i + 1].path = ft_strtrim2((*l)->content, " ");
	else
		(*cmd_array)[*i + 1].path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
}

void	ca22(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i].path = ft_strtrim2((*l)->content, " ");
	else
		(*cmd_array)[*i].path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
}

void	ca2(t_list **l, int *i, t_cmd **cmd_array, char **env)
{
	int	flag;

	flag = 0;
	while (((char *)((*l)->content))[0] == '<')
	{
		(*l) = (*l)->next;
		ft_putendl_fd(((char *)((*l)->content)), 2);
		ca22(l, i, cmd_array);
		(*cmd_array)[*i].args = NULL;
		(*cmd_array)[*i].type = RED_IN;
		(*l) = (*l)->next;
		(*i)++;
	}
	(*i)--;
	if (((char *)((*l)->next->content))[0] == '<' && ((char *)((*l)->next->next->content))[0] == '<')
	{
			ft_putendl_fd("HDOC Here", 2);
			(*cmd_array)[*i + 1] = handle_hdoc(l, env);
	}
	else
	{
		if (is_in_str('/', (*l)->content) == 0)
		{
			ft_putendl_fd((*l)->content, 2);
			if (ft_strncmp("built", ft_strtrim2((*l)->content, " "), 6) == 0) // NEED TO CHANGE TO DETECT_BUILTIN()
			{
				flag = 1;
				ft_putendl_fd("OOOOO", 2);
				(*cmd_array)[*i + 1].path = ft_strdup((*l)->content);
			}
			else
				(*cmd_array)[*i + 1].path = find_nice_path((*l)->content, env);
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
			if (flag == 1) // NEED TO CHANGE TO DETECT_BUILTIN()
				(*cmd_array)[*i + 1].type = BUILTIN;
			else
				(*cmd_array)[*i + 1].type = CMD;
		}
	}
}

void	ca32(t_list **l, int *i, t_cmd **cmd_array, int *j)
{
	if (((char *)((*l)->next->next->content))[0] == ' ' || (((char *)((*l)->next->next->content))[0] == '>' && (*l)->next->next->next))
	{
		free((*cmd_array)[*i + *j].path);
		(*cmd_array)[*i + *j].path = ft_strtrim2((*l)->next->next->content, " ");
	}
	else
		(*cmd_array)[*i + *j].path = ft_substr((*l)->next->next->content, 0, ft_strlen((*l)->next->next->content));
}

int	ca3(t_list **l, int *i, t_cmd **cmd_array, char **env, int *j)
{
	ca32(l, i, cmd_array, j);
	(*cmd_array)[*i + *j].args = NULL;
	if ((*cmd_array)[*i + *j].type != RED_APP)
		(*cmd_array)[*i + *j].type = RED_OUT;
	if (((char *)((*l)->content))[0] != '>')
		(*l) = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] != '|' && ((char *)((*l)->content))[0] != '>')
		(*l) = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] != '|' && ((char *)((*l)->content))[0] == '>')
		(*l) = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] == '>' && (*l)->next)
	{
		while (((char *)((*l)->content))[0] != '>')
			(*l) = (*l)->next;
		if (ft_strlen((*cmd_array)[*i + *j].path) != 0)
			(*cmd_array)[*i + *j + 1].type = RED_APP;
		else
			(*cmd_array)[*i + *j].type = RED_APP;
	}
	if (ft_strlen((*cmd_array)[*i + *j].path) != 0)
		(*j)++;
	return (0);
}

t_cmd	*create_args(t_list *l, int i, char **env)
{
	t_cmd	*cmd_array;
	int		j;

	j = 2;
	cmd_array = ft_calloc(ft_lstsize(l), sizeof(t_cmd));
	//if (((char *)(l->content))[0] == '<')
	//	l = l->next;
	while (l)
	{
		ft_putendl_fd(l->content, 2);
		ca2(&l, &i, &cmd_array, env);
		//l = l->next;
		while (l->next && ((char *)(l->next->content))[0] != '<')
		{
			ft_putstr_fd("VALUE :", 2);
			ft_putendl_fd(l->content, 2);
			ca3(&l, &i, &cmd_array, env, &j);
		}
		//while (l && ((char *)(l->content))[0] != '<')
		//	l = l->next;
		if (l)
		{
			ft_putstr_fd("VAL: ", 2);
			ft_putendl_fd(((char *)(l->content)), 2);
//			l = l->next;
		}
		if (l)
			l = l->next;
		i += j;
		j = 2;
	}
	cmd_array[i].type = END;
	i = 0;
	while (cmd_array[i].type != END)
	{
		ft_putstr_fd(cmd_array[i].path, 2);
		j = -1;
		ft_putchar_fd('|', 2);
		while (cmd_array[i].args && cmd_array[i].args[++j])
		{
			ft_putstr_fd(cmd_array[i].args[j], 2);
			ft_putchar_fd('|', 2);
		}
		ft_putnbr_fd(cmd_array[i].type, 2);
		ft_putchar_fd('\n', 2);
		i++;
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

int	do1cmd(t_cmd *cmds, int flag, char **env)
{
	int		fd[2];
	int		i;
	int		j;

	i = 0;
	flag = 0;
	ft_putendl_fd("AA", 2);
	ft_putendl_fd("AB", 2);
	fd[0] = open("/dev/stdin", O_RDONLY);
	while (cmds[i].type == RED_IN)
	{
		if (fd[0] == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmds[i - 1].path, 2);
			ft_putendl_fd(": No such file or directory", 2);
			flag = 1;
		}
		if (fd[0] != -1)
			close(fd[0]);
		fd[0] = open(cmds[i].path, O_RDONLY);
		i++;
	}
	j = i;
	i++;
	if (flag == 1)
		exit(127);
	if (cmds[i - 1].type == HDOC)
		return (ft_putendl_fd("Need to manage HDOC", 2), exit(3), 0);
	if (cmds[i - 1].type == NONE)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmds[i - 1].path, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	ft_putendl_fd("AC", 2);
	if (fd[0] == -1)
		return (ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmds[i - 2].path, 2), ft_putendl_fd(": No such file or directory", 2), exit(1), 0);
	ft_putendl_fd("AD", 2);
	dup2(fd[0], 0);
	ft_putendl_fd("AE", 2);
	close(fd[0]);
	ft_putendl_fd("AF", 2);
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	ft_putendl_fd("AG", 2);
	while (cmds[i].type != END)
		do1cmd2(fd, &i, cmds);
	ft_putendl_fd("AH", 2);
	if (fd[1] == -1)
		return (ft_putendl_fd("Error", 2), exit(1), 0);
	ft_putendl_fd("AI", 2);
	dup2(fd[1], 1);
	ft_putendl_fd("AJ", 2);
	close(fd[1]);
	ft_putendl_fd("AK", 2);
	if (execve(cmds[j].path, cmds[j].args, env))
		ft_putendl_fd("...", 2);
	ft_putendl_fd("AL", 2);
	exit(1);
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
int	builtin(t_cmd *cmd, char **env)
{
	int fd[2];
	int	i;

	i = 2;
	fd[0] = open(cmd[0].path, O_RDONLY);
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmd[i].type != END)
		do1cmd2(fd, &i, cmd);
	ft_putendl_fd("Hello word", fd[1]);
	ft_putendl_fd("???", 2);
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int	simulpipe(t_cmd **cmd, char **env)
{
	int status;
	int tab[3];
	t_cmd *type;
	pid_t pid;

	tab[0] = 0;
	while ((*cmd)[tab[0]].type != END)
	{
		tab[2] = tab[0];
		tab[1] = 0;
		simulpipe2(tab, *cmd, &type);
		if (type[1].type == BUILTIN)
		{
			status = builtin(type, env);
			free(type);
		}
		else
		{
			pid = fork();
			if (pid == 0)
				do1cmd(type, 0, env);
			else
			{
				waitpid(pid, &status, 0);
				free(type);
			}
		}
	}
	tab[0] = 0;
	while ((*cmd)[tab[0]].type != END)
	{
		//ft_putendl_fd(":::::", 2);
		free((*cmd)[tab[0]].path);
		if ((*cmd)[tab[0]].args)
			ft_free((*cmd)[tab[0]].args);
		(tab[0])++;
	}
	free(*cmd);
	exit(WEXITSTATUS(status));
	return (1);
}

void	apply_flags(t_list *t_lst, int flags[])
{
	if (t_lst == NULL)
	{
		ft_putendl_fd("....", 2);
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

int	main3(t_list *t_lst[], int flags[], char **env)
{
	t_cmd	*cmds;
	int f;

	f = 0;
	t_lst[0] = t_lst[1];
	ft_putendl_fd("A", 2);
	apply_flags(t_lst[0], flags);
	ft_putendl_fd("B", 2);
	t_lst[0] = t_lst[1];
	ft_putendl_fd("C", 2);
	cmds = create_args(t_lst[1], 0, env);
	ft_putendl_fd("D", 2);
	ft_lstclear(&t_lst[1], &ft_del);
	ft_putendl_fd("E", 2);
	//ft_putendl_fd(")))", 2);
	f = simulpipe(&cmds, env);
	return (f);
}

t_list	*lstdup(t_list *lst)
{
	t_list *new_lst;

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
	t_list	*cpy;
	char	*str;

	cpy = *lst;
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
	return (new_lst);
}

void	main2(char *str, char **env, int *flag, int fd)
{
	t_nlist	*lst;
	t_list	*t_lst[2];
	int		flags[6];
	pid_t	pid;
	char	**tab;
	char	*tempfilein[2] = {"< /tmp/tempfile ", "< /tmp/tempfile2 "};
	char	*tempfileout[2] = {"> /tmp/tempfile ", "> /tmp/tempfile2 "};

	fd = open("/tmp/tempfile", O_RDWR | O_CREAT, 0644);
	close(fd);
	fd = open("/tmp/tempfile2", O_RDWR | O_CREAT, 0644);
	close(fd);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		flags[4] = 0;
		tab = ft_split(str, '|');
		while (tab[flags[4]] != NULL)
		{
			if (tab[flags[4]][0] != '<')
			{
				if (flags[4] == 0)
					tab[flags[4]] = add_str2("< /dev/stdin ", &(tab[flags[4]]));
				else
					tab[flags[4]] = add_str2(tempfilein[(flags[4] + 1) % 2], &(tab[flags[4]]));
			}
			if (is_in_str('>', tab[flags[4]]) == 0)
			{
				if (tab[flags[4] + 1])
					tab[flags[4]] = add_str(tab[flags[4]], tempfileout[flags[4] % 2]);
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
		t_lst[0] = change_lst(&(t_lst[0]));
		
		t_lst[1] = interpret_quotes(t_lst[0], *flag);
		ft_lstclear(&(t_lst[0]), &ft_del);
		/*while (t_lst[1])
		{
			ft_putendl_fd(t_lst[1]->content, 2);
			t_lst[1] = t_lst[1]->next;
		}
		exit(6);*/
		nlstclear(&lst);
		ft_putendl_fd(str, 2);
		free(tab);
		free(str);
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
	int		fd;
	char	*str;

	flag = -1;
	while (1)
	{
		str = readline(">> ");
		if (str && str[0] != '\0')
			add_history(str);
		if (ft_strncmp(str, "exit", 5) == 0)
		{
			free(str);
			rl_clear_history();
			return (0);
		}
		if (only_in2(str, ' ', '	') == 1)
			continue ; 
		else
		{
			main2(str, env, &flag, fd);
			unlink("/tmp/tempfile");
			unlink("/tmp/tempfile2");
			free(str);
		}
	}
	return (1);
}

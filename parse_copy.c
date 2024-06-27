#include "Pipex/libft/libft.h"
#include "parser.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>

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
	ft_putendl_fd("HHHHH", 2);
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
		array[nb] = ft_strdup((*lst)->content);
		(*lst) = (*lst)->next;
		nb++;
	}
	array[nb] = ft_strdup((*lst)->content);
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

void	ca23(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i + 1].path = ft_substr((*l)->content, 1, ft_strlen((*l)->content) - 1);
	else
		(*cmd_array)[*i + 1].path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
}

void	ca22(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i].path = ft_substr((*l)->content, 1, ft_strlen((*l)->content) - 1);
	else
		(*cmd_array)[*i].path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
}

void	ca2(t_list **l, int *i, t_cmd **cmd_array, char **env)
{
	if (only_in((*l)->content, ' ') == 1 || only_in((*l)->content, '\t') == 1)
		exit(0);
	ca22(l, i, cmd_array);
	(*cmd_array)[*i].args = NULL;
	(*cmd_array)[*i].type = RED_IN;
	(*l) = (*l)->next;
	if (is_in_str('/', (*l)->content) == 0)
		(*cmd_array)[*i + 1].path = find_nice_path((*l)->content, env);
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
		(*cmd_array)[*i + 1].type = CMD;
	}
}

void	ca32(t_list **l, int *i, t_cmd **cmd_array, int *j)
{
	if (((char *)((*l)->content))[0] == ' ' || (((char *)((*l)->content))[0] == '>' && (*l)->next))
	{
		free((*cmd_array)[*i + *j].path);
		(*cmd_array)[*i + *j].path = ft_substr((*l)->content, 1, ft_strlen((*l)->content) - 1);
	}
	else
		(*cmd_array)[*i + *j].path = ft_substr((*l)->content, 0, ft_strlen((*l)->content));
}

int	ca3(t_list **l, int *i, t_cmd **cmd_array, char **env)
{
	int j;

	j = 2;
	ca32(l, i, cmd_array, &j);
	(*cmd_array)[*i + j].args = NULL;
	if ((*cmd_array)[*i + j].type != RED_APP)
		(*cmd_array)[*i + j].type = RED_OUT;
	if (((char *)((*l)->content))[0] != '>')
		(*l) = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] != '|' && ((char *)((*l)->content))[0] != '>')
		(*l) = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] == '>')
		(*l) = (*l)->next;
	if ((*l) && ((char *)((*l)->content))[0] == '>' && (*l)->next)
	{
		while (((char *)((*l)->content))[0] != '>')
			(*l) = (*l)->next;
		if (ft_strlen((*cmd_array)[*i + j].path) != 0)
			(*cmd_array)[*i + j + 1].type = RED_APP;
		else
			(*cmd_array)[*i + j].type = RED_APP;
	}
	if (ft_strlen((*cmd_array)[*i + j].path) != 0)
		j++;
	return (j);
}

t_cmd	*create_args(t_list *l, int i, char **env)
{
	t_cmd	*cmd_array;
	int		j;

	cmd_array = ft_calloc(ft_lstsize(l), sizeof(t_cmd));
	l = l->next;
	while (l)
	{
		ca2(&l, &i, &cmd_array, env);
		l = l->next;
		while (l && ((char *)(l->content))[0] != '|')
			j = ca3(&l, &i, &cmd_array, env);
		while (l && ((char *)(l->content))[0] != '<')
			l = l->next;
		if (l)
			l = l->next;
		i += j;
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

	i = 2;
	if (cmds[1].type == NONE)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmds[1].path, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	fd[0] = open(cmds[0].path, O_RDONLY);
	if (fd[0] == -1)
		exit(1);
	dup2(fd[0], 0);
	close(fd[0]);
	fd[1] = open("/dev/stdout", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (cmds[i].type != END)
		do1cmd2(fd, &i, cmds);
	if (fd[1] == -1)
		exit(1);
	dup2(fd[1], 1);
	close(fd[1]);
	execve(cmds[1].path, cmds[1].args, env);
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
void	simulpipe(t_cmd **cmd, char **env)
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
		pid = fork();
		if (pid == 0)
			do1cmd(type, 0, env);
		else
		{
			waitpid(pid, &status, 0);
			free(type);
		}
	}
	tab[0] = 0;
	while ((*cmd)[tab[0]].type != END)
	{
		ft_putendl_fd(":::::", 2);
		free((*cmd)[tab[0]].path);
		if ((*cmd)[tab[0]].args)
			ft_free((*cmd)[tab[0]].args);
		(tab[0])++;
	}
	exit(WEXITSTATUS(status));
}

void	apply_flags(t_list *t_lst, int flags[])
{
	if (t_lst == NULL)
		exit(1);
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

void	main3(t_list *t_lst[], int flags[], char **env)
{
	t_cmd	*cmds;
	int f;

	f = 0;
	t_lst[0] = t_lst[1];
	apply_flags(t_lst[0], flags);
	t_lst[0] = t_lst[1];
	cmds = create_args(t_lst[1], 0, env);
	ft_lstclear(&t_lst[1], &ft_del);
	ft_putendl_fd(")))", 2);
	simulpipe(&cmds, env);
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

	fd = open("/tmp/tempfile", O_RDWR | O_CREAT | O_TRUNC, 0644);
	close(fd);
	fd = open("/tmp/tempfile2", O_RDWR | O_CREAT | O_TRUNC, 0644);
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
			if (is_in_str('<', tab[flags[4]]) == 0)
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
			str = add_str(str, "| ");
			str = add_str(str, tab[flags[4]]);
			free(tab[flags[4]]);
			flags[4] += 1;
		}
		flags[4] = 0;
		while (++(flags[4]) < 4)
			flags[flags[4]] = 0;
		lst = create_stack_1(str);
		t_lst[0] = create_stack3(lst);
		t_lst[1] = interpret_quotes(t_lst[0], *flag);
		ft_lstclear(&(t_lst[0]), &ft_del);
		nlstclear(&lst);
		ft_putendl_fd(str, 2);
		free(tab);
		main3(t_lst, flags, env);
	}
	else
	{
		waitpid(pid, &(flags[5]), 0);
		*flag = WEXITSTATUS(flags[5]);
	}
}

void enable_raw_mode(struct termios *orig_termios) {
    struct termios raw;

    tcgetattr(STDIN_FILENO, orig_termios);
    raw = *orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(struct termios *orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

int	main(int c, char **v, char **env)
{
	int		flag;
	int		fd;
	char	*str;
	char	sub[2];
	struct termios orig_termios;
	
	sub[0] = '\0';
	sub[1] = '\0';
	flag = -1;
	str = ft_calloc(2, 1);
	//sub = ft_strdup("");
	enable_raw_mode(&orig_termios);
	ft_putstr_fd(">> ", 1);
	read(STDIN_FILENO, str, 1);
	//ft_putstr_fd("caracter reached : ", 2);
	ft_putstr_fd(str, 2);
	while (1)
	{
		while (sub[0] != '\n')
		{
			read(STDIN_FILENO, sub, 1);
			write(STDOUT_FILENO, "\033[2K\r", 5);
			ft_putstr_fd(">> ", 1);
			str = add_str(str, sub);
			//ft_putstr_fd("caracter reached : ", 2);
			ft_putstr_fd(str, 2);
		}
		ft_putendl_fd(str, 2);
		exit(2);
		if (ft_strncmp(str, "exit", 5) == 0)
			return (disable_raw_mode(&orig_termios), 0);
		main2(str, env, &flag, fd);
		unlink("/tmp/tempfile");
		unlink("/tmp/tempfile2");
	}
	return (1);
}

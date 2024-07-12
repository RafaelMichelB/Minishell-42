#include "parser.h"

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

void	open_fds(int fd)
{
	fd = open("/tmp/tempfile", O_RDWR | O_CREAT, 0644);
	close(fd);
	fd = open("/tmp/tempfile2", O_RDWR | O_CREAT, 0644);
	close(fd);
}

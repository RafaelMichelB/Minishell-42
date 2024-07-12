#include "parser.h"

void	cl(t_list **cp, t_list **tmp)
{
	if (((char *)(*cp)->content)[0] == '<' && \
			((char *)(*cp)->next->content)[0] == '<')
	{
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup(";")));
		(*cp) = (*cp)->next;
	}
	else
		ft_lstadd_back(tmp, ft_lstnew(ft_strdup((*cp)->content)));
	(*cp) = (*cp)->next;
}

void	cl2(t_list **cp, t_list **new_lst, t_list **tmp_lst)
{
	if (((char *)(*cp)->content)[0] == '<')
	{
		ft_lstadd_back(new_lst, ft_lstnew(ft_strdup("<")));
		ft_lstadd_back(new_lst, ft_lstnew(ft_strdup((*cp)->next->content)));
		(*cp) = (*cp)->next;
	}
	else if (((char *)(*cp)->content)[0] == '|')
	{
		if (*new_lst == NULL)
			*new_lst = lstdup(*tmp_lst);
		else
			ft_lstlast(*new_lst)->next = lstdup(*tmp_lst);
		ft_lstclear(tmp_lst, &ft_del);
		*tmp_lst = NULL;
	}
	else
		ft_lstadd_back(tmp_lst, ft_lstnew(ft_strdup((*cp)->content)));
	(*cp) = (*cp)->next;
}

t_list	*change_lst(t_list **lst)
{
	t_list	*new_lst;
	t_list	*tmp_lst;
	t_list	*tmp;
	t_list	*cp;
	char	*str;

	tmp = NULL;
	cp = *lst;
	while (cp)
		cl(&cp, &tmp);
	cp = tmp;
	new_lst = NULL;
	tmp_lst = NULL;
	str = cp->next->content;
	cp = cp->next->next;
	while (cp)
		cl2(&cp, &new_lst, &tmp_lst);
	if (new_lst == NULL)
		new_lst = lstdup(tmp_lst);
	else
		ft_lstlast(new_lst)->next = lstdup(tmp_lst);
	return (ft_lstadd_front(&new_lst, ft_lstnew(ft_strdup(str))), \
	ft_lstadd_front(&new_lst, ft_lstnew(ft_strdup("<"))), \
	ft_lstclear(&tmp_lst, &ft_del), ft_lstclear(&tmp, &ft_del), new_lst);
}

t_cmd	*main3(t_list *t_lst[], t_nlist *lst, int *flag, t_env **env)
{
	t_cmd	*cmds;

	t_lst[0] = create_stack3(lst);
	t_lst[2] = change_lst(&(t_lst[0]));
	t_lst[1] = interpret_quotes(t_lst[2], *flag, *env);
	ft_lstclear(&(t_lst[0]), &ft_del);
	ft_lstclear(&(t_lst[2]), &ft_del);
	nlstclear(&lst);
	t_lst[0] = t_lst[1];
	cmds = create_args(t_lst[1], *env);
	ft_lstclear(&(t_lst[1]), &ft_del);
	return (cmds);
}

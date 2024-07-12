#include "parser.h"

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

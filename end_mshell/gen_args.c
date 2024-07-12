#include "parser.h"

void	ga2(int *nb, t_list **lst, char **array)
{
	if (only_in((*lst)->content, ' '))
	{
		(*nb)--;
		(*lst) = (*lst)->next;
	}
	else if (((char *)((*lst)->content))[0] == ' ')
	{
		array[*nb] = ft_strtrim2((*lst)->content, " ");
		(*lst) = (*lst)->next;
	}
	else
	{
		array[*nb] = ft_substr((*lst)->content, 0, \
				ft_strlen((*lst)->content));
		(*lst) = (*lst)->next;
	}
	(*nb)++;
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
		ga2(&nb, lst, array);
	if (((char *)((*lst)->content))[0] == ' ')
		array[nb] = ft_strtrim2((*lst)->content, " ");
	else
		array[nb] = ft_substr((*lst)->content, 0, ft_strlen((*lst)->content));
	return (array);
}

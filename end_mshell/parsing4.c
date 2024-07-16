/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:34 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:50:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

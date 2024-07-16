/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:49:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ca25(t_list **l, int *i, t_cmd **cmd_array)
{
	(*l) = (*l)->next;
	ca22(l, i, cmd_array);
	(*cmd_array)[*i].args = NULL;
	(*cmd_array)[*i].type = RED_IN;
	(*l) = (*l)->next;
	(*i)++;
}

void	ca2(t_list **l, int *i, t_cmd **cmd_array, t_env *env)
{
	while (((char *)((*l)->content))[0] == '<')
		ca25(l, i, cmd_array);
	(*i)--;
	if (((char *)((*l)->content))[0] == ';')
		(*cmd_array)[*i + 1] = handle_hdoc2(l, env);
	else if (((char *)((*l)->next->content))[0] == ';')
		(*cmd_array)[*i + 1] = handle_hdoc(l, env);
	else
		ca26(l, &env, cmd_array, i);
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
	while (*l && ((char *)((*l)->content))[0] != '>')
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
		ca2(&l, &(tab[0]), &cmd_array, env);
		while (l && l->next && ((char *)(l->next->content))[0] != '<')
			ca3(&l, tab, &cmd_array);
		if (l)
			l = l->next;
		tab[0] += tab[1];
		tab[1] = 2;
	}
	cmd_array[tab[0]].type = END;
	return (cmd_array);
}

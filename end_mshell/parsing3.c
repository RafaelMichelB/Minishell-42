/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:50:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	iq42(t_nlist *stacks[], char *strs[], int flag)
{
	char	*str;

	if (stacks[2] == NULL || stacks[2]->c == ' ')
	{
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

void	iq322(t_nlist *stacks[], char *strs[], int flag, t_env *env)
{
	int	f;

	(void)flag;
	f = 0;
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
}

void	iq32(t_nlist *stacks[], char *strs[], int flag, t_env *env)
{
	stacks[2] = stacks[2]->next;
	if (stacks[2]->c == ' ' || stacks[2]->c == '"')
	{
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
		iq322(stacks, strs, flag, env);
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

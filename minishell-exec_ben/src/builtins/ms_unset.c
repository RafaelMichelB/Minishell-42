/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:56:17 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/14 02:56:17 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_var(char *search, char *senvp)
{
	int	i;

	i = 0;
	while (search[i] != '\0')
	{
		if (search[i] != senvp[i])
			return (-1);
		i++;
	}
	if (senvp[i] == '=')
		return (0);
	return (-1);
}

int	ms_unset(t_parser *data, int i, int j)
{
	printf("arg unset %s\n", data->command->cmd_ex[1]);
	data->cmd_builtin++;
	if (data->command->cmd_ex[1] == NULL)
		return (set_error(data, 127), 1);
	while (data->command->cmd_ex[++j] != NULL)
	{
		i = -1;
		while (data->envp[++i] != NULL)
		{
			if (search_var(data->command->cmd_ex[j], data->envp[i]) == 0)
				break ;
		}
		printf("apres search result %s\n", data->envp[i]);
		if (data->envp[i] != NULL) //1 = supr
			data->envp = suprlineenvp(data, i);/* 1,*/
		else
			printf("error missing var %s\n",
				data->command->cmd_ex[1]);
	}
	return (0);
}

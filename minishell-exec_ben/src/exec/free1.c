/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 07:37:44 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/23 22:18:14 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_parser *data)
{
	free_split_str(data->envp);
	//free(data);
	//free_parser(data, -1);//free all lst and struct
}

void	free_ex(t_parser *data)
{
	int	i;

	i = -1;
	if (data->tab_path != NULL)
		freetab_path(data);
	if (data->pipefd != NULL)
	{
		while (++i != data->size_li)
			free(data->pipefd[i]);
		free(data->pipefd);
		data->pipefd = NULL;
	}
	free_command(data);
	printf("Hello W\n");
	//probleme de free dans les enfants ?
}

void	freetab_path(t_parser *data)
{
	int	i;

	i = 0;
	while (data->tab_path[i] != NULL)
	{
		free(data->tab_path[i]);
		i++;
	}
	free(data->tab_path);
	data->tab_path = NULL;
}

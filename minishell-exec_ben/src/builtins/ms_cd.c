/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:55:18 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/14 02:55:18 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(t_parser *data)
{
	data->cmd_builtin++;
	if (data->command->cmd_ex[1] == NULL)
		return (printf("error: no argument\n"), set_error(data, 127), 0);
	// Change directory
	if (chdir(data->command->cmd_ex[1]) != 0)
		return (perror("cd"), set_error(data, 127), 0);
	else
	{
		printf("Directory changed to %s\n",
			data->command->cmd_ex[1]);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:02:55 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/22 14:04:40 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*checkaccess(char *cmd, char **split_path)
{
	int		i;
	char	*test;

	i = 0;
	if (cmd[i] == '.' && cmd[i + 1] == '/')
		return (cmd);
	while (split_path[i] != NULL)
	{
		//printf("path : %s\n", split_path[i]);
		test = ft_strjoin(split_path[i], cmd, 1);
		if (access(test, X_OK) == 0)
			return (test);
		free(test);
		i++;
	}
	return (NULL);
}

int	ft_strncmp(char *str, int n)
{
	int		i;
	char	*cmp;

	cmp = "PATH";
	i = 0;
	while ((str[i] != '\0' && cmp[i] != '\0') || i < n)
	{
		if (str[i] == cmp[i])
			i++;
		else if (str[i] != cmp[i])
			return (0);
	}
	return (1);
}

void	set_error(t_parser *data, int code)
{
	data->handle_error = code;
	printf("val error return %d\n", data->handle_error);
}

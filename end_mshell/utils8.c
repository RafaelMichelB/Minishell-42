/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:59:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/16 17:59:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ex3(t_cmd *cmd, int i, int fd[], t_env **env)
{
	if (access(cmd[i - 1].path, F_OK) == 0 && \
	access(cmd[i - 1].path, W_OK) != 0)
		return (ft_putstr_fd("bash: ", 2), \
ft_putstr_fd(cmd[i - 1].path, 2), \
ft_putendl_fd(": Permission denied", 2), env_clear(env), close(fd[0]), 1);
	return (close(fd[0]), 1);
}

int	numerics(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (1);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '"' && s[i] != '+' && s[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

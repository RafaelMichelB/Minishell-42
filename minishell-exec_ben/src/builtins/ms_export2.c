/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:18:36 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/22 13:39:35 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setvar(t_parser *data, char *str)
{
	int		len;
	int		i;
	char	**cpy;

	i = -1;
	len = 0;
	while (data->envp[len] != NULL)
		len++;
	cpy = (char **)malloc(sizeof (char *) * (len + 2));
	while (data->envp[++i] != NULL)
		cpy[i] = ft_strdup(data->envp[i]);
	cpy[i] = ft_strdup(str);
	cpy[i + 1] = NULL;
	free_split_str(data->envp);
	data->envp = cpy;
	//ms_env(data, NULL, );//pour verifie
}

void	modif_var(t_parser *data, char *val, int i)
{
	int	j;

	while (data->envp[++i] != NULL)
	{
		j = -1;
		while (data->envp[i][++j] != '=')
		{
			if (data->envp[i][j] != val[j])
				break ;
		}
		if (val[j] == '=' && data->envp[i][j] == '=' && val[j + 1] != '\0')
			break ;
	}
	data->envp = suprlineenvp(data, i);
	setvar(data, val);
}

char	**suprlineenvp(t_parser *data, int i)
{
	int		len;
	int		tlen;
	int		k;
	char	**cpy;

	tlen = 0;
	while (data->envp[tlen] != NULL)
		tlen++;
	cpy = (char **)malloc(sizeof (char *) * (tlen));
	len = -1;
	k = 0;
	while (data->envp[++len] != NULL)
	{
		//printf("test suprline %s\n", data->envp[len]);
		if (len == i && len != tlen - 1) //ligne a supr
			len++;
		else if (len == tlen - 1)
			break ;
		cpy[k] = ft_strdup(data->envp[len]);
		k++;
	}
	cpy[k] = NULL;
	free_split_str(data->envp);
	return (cpy);
}

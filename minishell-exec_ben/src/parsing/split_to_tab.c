/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estepere <estepere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:22:59 by estepere          #+#    #+#             */
/*   Updated: 2024/10/18 20:06:07 by estepere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pars.h"


// len for the array
int	ft_nb_array(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '|'&& (ft_is_between_s_quote(line, i) == 0 ||
			ft_is_between_d_quote(line, i)) == 0)
			j++;
		i++;
	}
	if (j > 0)
		return (i + 1);
	else
		return (1);
}





char	*ft_replace_line(char *line, int pos_pipe)
{
	int	i;
	char *new_line;
	
	i = 0;
	new_line = malloc(sizeof(char *) * (ft_strchr_pipe(line) + 1));
	while (line[i] && i < pos_pipe)
	{
		new_line[i] = line[i];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

int	ft_tab_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
t_command	*ft_split_line_to_cmd(t_command *command)
{
	char	**tab;
	int	i;

	i = 0;
	tab = ft_split_of_the_death(command->line, ' ');	
	command->cmd_ex = malloc(sizeof(char  *) * (ft_tab_len(tab) + 1));
	while (tab[i])
	{
		command->cmd_ex[i] = ft_strdup(tab[i]);
		i++;
	}
	command->cmd_ex[i] = NULL;
	// ft_free_tab_tab
	
	return (command);
}





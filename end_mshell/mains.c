/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mains.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:52 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:49:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	main2(char *str, t_env **env, int *flag, int fd)
{
	t_nlist		*lst;
	t_list		*t_lst[3];
	int			flags[6];
	char		**tab;
	t_cmd		*cmds;

	open_fds(fd);
	flags[4] = 0;
	tab = ft_splitnochain(str, '|');
	tab[flags[4]] = add_str2("< /dev/stdin ", &(tab[flags[4]]));
	while (tab[flags[4]] != NULL)
		change_st(tab, flags);
	flags[4] = 1;
	str = ft_strdup(tab[0]);
	free(tab[0]);
	while (tab[flags[4]] != NULL)
		change_st2(&str, &tab, flags);
	flags[4] = 0;
	while (++(flags[4]) < 4)
		flags[flags[4]] = 0;
	lst = create_stack_1(str);
	cmds = main3(t_lst, lst, flag, env);
	free(tab);
	free(str);
	*flag = simulpipe(cmds, env);
}

void	handle_sigint(int sig)
{
	(void)sig;
	hold_flag('p', 130);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("\n[Minishell] > ", 1);
	return ;
}

void	main12(char *str, t_env **my_env, int flag)
{
	free(str);
	rl_clear_history();
	env_clear(my_env);
	exit(flag);
}

void	main13(char ***t, int flag, char *str, t_env **my_env)
{
	if ((*t)[1] && (*t)[2])
	{
		ft_putendl_fd("bash: exit: too many args", 2);
		return ;
	}
	if ((*t)[1])
		flag = ft_atoi2((*t)[1]);
	ft_free(*t);
	free(str);
	rl_clear_history();
	env_clear(my_env);
	exit(flag);
}

char	**ft_splitnochain(char *str, char c)
{
	char	**ret;
	int		i;

	i = 0;
	ret = ft_split(str, c);
	str = ft_strchr(str, c);
	while (str != NULL)
	{
		while (*(++str) == c)
			ret[i] = add_str(ret[i], "|");
		i++;
		str = ft_strchr(str, c);
	}
	return (ret);
}

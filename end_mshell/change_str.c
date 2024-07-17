/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:49:04 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:49:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_nb(char *s, char c)
{
	int	i;
	int	nb;

	nb = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			nb++;
	}
	return (nb);
}

void	cs(char **tab, int f[], char *tin[])
{
	if (count_nb(tab[f[4]], '"') % 2 == 0 && \
	count_nb(tab[f[4]], '\'') % 2 == 0)
		tab[f[4]] = add_str2(tin[(f[4] + 1) % 2], &(tab[f[4]]));
}

void	change_st(char **tab, int f[])
{
	static char	*tin[2] = {"< /tmp/tempfile ", "< /tmp/tempfile2 "};
	static char	*to[2] = {"> /tmp/tempfile ", "> /tmp/tempfile2 "};

	if (tab[f[4]][0] != '<')
	{
		ft_putendl_fd(tab[f[4]], 2);
		if (f[4] == 0)
			tab[f[4]] = add_str2("< /dev/stdin ", &(tab[f[4]]));
		else
			cs(tab, f, tin);
	}
	if (is_in_str('>', tab[f[4]]) == 0)
	{
		if (tab[f[4] + 1])
		{
			if (count_nb(tab[f[4]], '"') % 2 == 0 && \
			count_nb(tab[f[4]], '\'') % 2 == 0)
				tab[f[4]] = add_str(tab[f[4]], to[f[4] % 2]);
			else if (tab[f[4] + 1] && (count_nb(tab[f[4] + 1], '"') % 2 == 0 && \
			count_nb(tab[f[4] + 1], '\'') % 2 == 0))
				tab[f[4]] = add_str(tab[f[4]], to[f[4] % 2]);
		}
		else
			tab[f[4]] = add_str(tab[f[4]], "> /dev/stdout");
	}
	f[4] += 1;
}

void	change_st2(char **str, char ***tab, int flags[])
{
	*str = add_str(*str, "|");
	*str = add_str(*str, (*tab)[flags[4]]);
	free((*tab)[flags[4]]);
	flags[4] += 1;
}

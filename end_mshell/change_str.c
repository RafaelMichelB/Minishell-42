#include "parser.h"

void	change_st(char **tab, int f[])
{
	static char	*tin[2] = {"< /tmp/tempfile ", "< /tmp/tempfile2 "};
	static char	*to[2] = {"> /tmp/tempfile ", "> /tmp/tempfile2 "};

	if (tab[f[4]][0] != '<')
	{
		if (f[4] == 0)
			tab[f[4]] = add_str2("< /dev/stdin ", &(tab[f[4]]));
		else
		{
			if (ft_strchr(tab[0], '"') == NULL)
				tab[f[4]] = add_str2(tin[(f[4] + 1) % 2], &(tab[f[4]]));
		}
	}
	if (is_in_str('>', tab[f[4]]) == 0)
	{
		if (tab[f[4] + 1])
		{
			if (ft_strchr(tab[0], '"') == NULL)
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

# include "pars.h"

int	ft_is_between_d_quote(char *str, int i)
{
	int	start;
	int	flag_before;
	int	flag_after;

	flag_before = 0;
	flag_after = 0;
	start = i;
	while (str[i] && i > 0)
	{
		if (str[i] == '"')
			flag_before++;
		i--;
	}
	i = start;
	while (str[i])
	{
		if (str[i] == '"')
			flag_after++;
		i++;
	}
	if (flag_before > 0 && flag_after > 0)
		return (1);
	return (0);
}

int	ft_is_between_s_quote(char *str, int i)
{
	int	start;
	int	flag_before;
	int	flag_after;

	flag_before = 0;
	flag_after = 0;
	start = i;
	while (str[i] && i > 0)
	{
		if (str[i] == '\'')
			flag_before++;
		i--;
	}
	i = start;
	while (str[i])
	{
		if (str[i] == '\'')
			flag_after++;
		i++;
	}
	if (flag_before > 0 && flag_after > 0)
		return (1);
	return (0);
}

int	ft_is_between_quote(char *str, int i)
{
	if (ft_is_between_s_quote(str, i) == 1 || ft_is_between_d_quote(str, i) == 1)
		return (1);
	return (0);
}
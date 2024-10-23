//#include "pars.h"

int	ft_countword(char const *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		// if (str[i] == '|' && !ft_is_between_quote(str, i))
		// 	return (nb);
		while (str[i] && str[i] == c && !ft_is_between_quote(str, i))
			i++;
		if (str[i])
		{
			if (str[i] == '|')
				nb--;
			nb++;
		}
		while (str[i])
		{
			if (str[i] == c && !ft_is_between_quote(str, i))
				break ;
			i++;
		}
	}
	return (nb);
}

int	ft_lenword(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_free_all(char **str, int j)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	str = NULL;
	return (str);
}

char	**ft_split_of_the_death(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	str = (char **)ft_calloc(sizeof(char *), (ft_countword(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c)
		{
			str[j] = ft_substr(s, i, ft_lenword(&s[i], c));
			if (!str[j])
				return (ft_free_all(str, j - 1));
			i = i + ft_lenword(&s[i], c);
			j++;
		}
		else
			i++;
	}
	return (str);
}
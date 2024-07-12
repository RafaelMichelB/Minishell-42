#include "parser.h"

char	**ft_split1(char *str, char c)
{
	char	**split;
	int		i;

	split = ft_split(str, c);
	i = 2;
	if (split[1] == NULL)
		return (split);
	while (split[i])
	{
		split[1] = add_str(split[1], "=");
		split[1] = add_str(split[1], split[i]);
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	return (split);
}

char	*ft_strjoin3elem(char *s1, char *s2, char *s3)
{
	char	*ret;
	char	*ret2;

	ret = ft_strjoin(s1, s2);
	if (s3)
		ret2 = ft_strjoin(ret, s3);
	else
		ret2 = ft_strjoin(ret, "");
	free(ret);
	return (ret2);
}

int	is_in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*add_str(char *str, char *s)
{
	char	*ret;

	ret = ft_strjoin(str, s);
	free(str);
	return (ret);
}

char	*add_str2(char *str, char **s)
{
	char	*ret;

	ret = ft_strjoin(str, *s);
	free(*s);
	return (ret);
}

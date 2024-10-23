# include "pars.h"


int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != (s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (0);
}
char	*ft_strndup(const char *s, int i)
{
	char	*dest;
	int	j;

	j = 0;	
	dest = (char *)malloc(sizeof(char) * (ft_lenn(s, i) + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
char	*ft_strdup(char *s)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (ft_lenn(s, 0) + 1));
	if (dest == NULL)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


int	ft_lenn(const char *str, int i)
{
	while (str[i])
		i++;
	return (i);
}

#include "pars.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lens;
	char	*str;
	size_t	i;

	i = 0;
	lens = ft_lenn(s, 0);
	if (start >= lens)
		return (ft_strdup(""));
	if (len + start >= lens)
		str = ft_calloc(sizeof(char), ((lens - start) + 1));
	if (start + len < lens)
		str = ft_calloc(sizeof(char), len + 1);
	if (!str)
		return (NULL);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
void	*ft_calloc(size_t n, size_t size)
{
	void	*p;
	size_t	len;

	len = n * size;
	p = malloc(len);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, len);
	return ((void *)p);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

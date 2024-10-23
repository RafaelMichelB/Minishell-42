
#include "minishell.h"

int	compare(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_size(t_command **li)
{
	int				i;
	t_command	*temp;

	i = 0;
	temp = *li;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
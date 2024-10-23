

#include "pars.h"



int	ft_countword(char const *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		printf("\nstr[i] : %c\ni: %d\n", str[i], i);
		while (str[i] && str[i] == c /*&& !ft_is_between_quote((char *)str, i)*/)
			i++;
		if (str[i]) {
			nb++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	return (nb);
}

int	ft_is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_lenword(char const *str, char c)
{
	int	i;

	i = 0;
	while ((str[i] && str[i] != c && !ft_is_redir(str[i])) || ft_is_between_quote((char *)str, i) == 1)
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

void ft_free_node(void *node)
{
	free(node);
}

char **convert_to_array(t_list *lst)
{
	char **array;
	int i;

	i = 0;
	array = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		array[i] = ft_strdup(lst->content);
		i++;
		lst = lst->next;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split_of_the_death(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;
	t_list *lst;

	lst = NULL;
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] == '<' || s[i + 1] == '>')
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(s, i, 2)));
				i = i + 2;
			}
			else
			{
				ft_lstadd_back(&lst, ft_lstnew(ft_substr(s, i, 1)));
				i = i + 1;
				j++;
			}
		}
		if (s[i] == '"')
		{
			j = i;
			i++;
			while (s[i] != '"')
				i++;
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(s, j, i - j + 1)));
			i++;
		}
		if (s[i] == '\'')
		{
			j = i;
			i++;
			while (s[i] != '\'')
				i++;
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(s, j, i - j + 1)));
			i++;
		}
		if (s[i] && s[i] != c)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(s, i, ft_lenword(&s[i], c))));
			if(s[i])
				i = i + ft_lenword(&s[i], c);
		}
		else
		{
			if (s[i])
				i++;
		}
	}
	str = convert_to_array(lst);
	ft_lstclear(&lst, &ft_free_node);
	return (str);
}

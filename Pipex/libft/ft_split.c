/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:19:11 by dbonali           #+#    #+#             */
/*   Updated: 2023/10/24 17:28:45 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	ft_count(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (i == 0 && str[i] != c)
			count++;
		if (i > 0)
		{
			if (str[i] != c && str[i - 1] == c)
				count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_fill_tab(char *str, char c, int count, char **tab)
{
	int	start;
	int	len;
	int	i;

	start = 0;
	len = 0;
	i = 0;
	while (i < count)
	{
		if (str[len] == c || str[len] == '\0')
		{
			if (len > 0 && str[len - 1] != c)
			{
				tab[i] = ft_substr(str, start, (len - start));
				if (tab[i] == NULL)
					return (ft_free(tab), NULL);
				i++;
			}
			while (str[len] == c)
				len++;
			start = len;
		}
		len++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	char	*str;
	int		count;

	if (*s == '\0')
	{
		tab = (char **)ft_calloc(1, sizeof(char *));
		if (tab == NULL)
			return (NULL);
		return (tab);
	}
	else
	{
		count = ft_count(s, c);
		str = ft_strdup(s);
		if (str == NULL)
			return (NULL);
		tab = (char **)ft_calloc((count + 1), sizeof(char *));
		if (tab != NULL)
			tab = ft_fill_tab(str, c, count, tab);
		if (tab == NULL)
			return (free(str), NULL);
	}
	free(str);
	return (tab);
}
/*
int	main()
{
        char    **tab = NULL;
        int     i;

        tab = ft_split("xxxxxxxxxxxxxhelloxxxxxhello", 'x');
        i = 0;
        while (tab[i])
        {
                printf("%s\n",tab[i]);
		i++;
        }
        ft_free(tab);
        return (0);
}*/

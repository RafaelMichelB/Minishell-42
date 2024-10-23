/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <rmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:50:00 by rmichel-          #+#    #+#             */
/*   Updated: 2024/07/12 16:22:11 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	all_sep(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			return (0);
		i++;
	}
	return (1);
}

static long	count_words(const char *s, char c)
{
	size_t	nb;
	size_t	looked_char;

	if (ft_strlen(s) == 0 || all_sep(s, c))
		return (0);
	looked_char = 0;
	nb = 0;
	while (s[looked_char] != '\0')
	{
		if (s[looked_char] != c)
		{
			nb++;
			while (s[looked_char] != c && s[looked_char + 1] != '\0')
				looked_char++;
		}
		looked_char++;
	}
	return (nb);
}

void	ft_free(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*count_size(size_t *looked_char, char *s, char c)
{
	size_t	size;
	char	*word;

	size = 0;
	while (s[*looked_char] != c && s[*looked_char] != '\0')
	{
		size++;
		(*looked_char)++;
	}
	if (size == 0)
	{
		word = ft_calloc(1, sizeof(char));
		if (word == NULL)
			return (NULL);
		return (word);
	}
	return (ft_substr(s, *looked_char - size, size));
}

char	**ft_split(char const *s, char c)
{
	char	**st_ar;
	long	actual_word;
	size_t	looked_char;
	long	i;

	i = count_words(s, c);
	looked_char = 0;
	actual_word = 0;
	st_ar = ft_calloc((i + 1), sizeof(char *));
	if (st_ar == NULL)
		return (NULL);
	while (i > actual_word)
	{
		st_ar[actual_word] = count_size(&looked_char, (char *)s, c);
		if (st_ar[actual_word] == NULL)
			return (ft_free(st_ar), NULL);
		if (ft_strncmp(st_ar[actual_word], "\0", ft_strlen(st_ar[actual_word])))
			actual_word++;
		else
			free(st_ar[actual_word]);
		looked_char++;
	}
	st_ar[actual_word] = NULL;
	return (st_ar);
}

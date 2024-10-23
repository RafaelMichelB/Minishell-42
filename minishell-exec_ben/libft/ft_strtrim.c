/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:38:24 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/13 10:13:46 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	all_in(const char *s, const char *set)
{
	size_t	i;
	size_t	carac;
	int		is_is_in;

	carac = 0;
	i = 0;
	while (s[i] != '\0')
	{
		is_is_in = is_in(s[i], set);
		if (is_is_in != 0)
			carac++;
		i++;
	}
	return (carac);
}

static char	*cut_str(const char *s, size_t start, size_t end, const char *set)
{
	int		is_is_in;
	char	*trimmed_str;

	is_is_in = is_in(s[start], set);
	while (is_is_in)
	{
		start++;
		is_is_in = is_in(s[start], set);
	}
	is_is_in = is_in(s[end], set);
	while (is_is_in)
	{
		end--;
		is_is_in = is_in(s[end], set);
	}
	trimmed_str = ft_substr(s, start, end - start + 1);
	return (trimmed_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_str;
	int		end;
	int		is_all_in;

	is_all_in = all_in(s1, set);
	end = ft_strlen(s1);
	if (is_all_in == end)
	{
		trimmed_str = ft_calloc(1, sizeof (char));
		return (trimmed_str);
	}
	trimmed_str = cut_str(s1, 0, end - 1, set);
	return (trimmed_str);
}

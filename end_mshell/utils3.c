/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:50:56 by marvin            #+#    #+#             */
/*   Updated: 2024/07/14 15:50:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_strtrim2(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (*s1 == '\0' || *set == '\0')
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	ptr = ft_substr(s1, start, (end - start));
	return (ptr);
}

int	abs(int i)
{
	if (i < 0)
		i *= (-1);
	return (i);
}

int	in_env(t_env *env, char *s)
{
	while (env)
	{
		if (ft_strncmp(env->key, s, 2147483647) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

t_env	*order_env(t_env *env)
{
	t_env	*ret;
	char	**array;
	char	*tmp;
	int		i;
	int		j;

	array = convert_array(env);
	i = -1;
	while (array[(++i) + 1] != NULL)
	{
		j = 0;
		while (array[j + 1] != NULL)
		{
			if (ft_strncmp(array[j], array[j + 1], 2147483647) > 0)
			{
				tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
			j++;
		}
	}
	ret = generate_env2(array);
	ft_free(array);
	return (ret);
}

#include "parser.h"

void	ca23(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i + 1].path = ft_strtrim2((*l)->content, " ");
	else
		(*cmd_array)[*i + 1].path = ft_substr((*l)->content, 0, \
				ft_strlen((*l)->content));
}

void	ca22(t_list **l, int *i, t_cmd **cmd_array)
{
	if (((char *)((*l)->content))[0] == ' ')
		(*cmd_array)[*i].path = ft_strtrim2((*l)->content, " ");
	else
		(*cmd_array)[*i].path = ft_substr((*l)->content, 0, \
				ft_strlen((*l)->content));
}

void	ca262(int *i, t_cmd **cmd_array, t_list **l, int flag)
{
	if ((*cmd_array)[*i + 1].path == NULL)
	{
		(*cmd_array)[*i + 1].path = ft_strdup((*l)->content);
		(*cmd_array)[*i + 1].args = NULL;
		(*cmd_array)[*i + 1].type = NONE;
		ft_free(gen_args(l));
	}
	else
	{
		(*cmd_array)[*i + 1].args = gen_args(l);
		if (flag == 1)
			(*cmd_array)[*i + 1].type = BUILTIN;
		else
			(*cmd_array)[*i + 1].type = CMD;
	}
}

void	ca26(t_list **l, t_env **env, t_cmd **cmd_array, int *i)
{
	int		flag;
	char	*s;
	char	**nenv;

	flag = 0;
	if (is_in_str('/', (*l)->content) == 0)
	{
		s = ft_strtrim2((*l)->content, " ");
		if (detect_builtin(s) == 0)
		{
			free(s);
			flag = 1;
			(*cmd_array)[*i + 1].path = ft_strdup((*l)->content);
		}
		else
		{
			free(s);
			nenv = convert_array(*env);
			(*cmd_array)[*i + 1].path = find_nice_path((*l)->content, nenv);
			ft_free(nenv);
		}
	}
	else
		ca23(l, i, cmd_array);
	ca262(i, cmd_array, l, flag);
}

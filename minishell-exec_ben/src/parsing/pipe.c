# include "pars.h"

int	ft_strchr_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && !ft_is_between_quote(str, i))
			return (i);
		i++;
	}
	return (0);

}
void	ft_parse_line(t_command *command, t_parser *data)
{
	int	i;
	char *cpy;
	t_command	*first_node;

	
	cpy = ft_str_var(data, ft_strdup(command->line), NULL, -1);
	first_node = command;
	command->line = cpy;
	ft_parse_pipe(command);
	while (command)
	{
		printf("line = %s\n", command->line);
		command = command->next;
	}
	command = first_node;
	while (command)
	{
		i = 0;
		command->cmd_ex = ft_split_of_the_death(command->line, ' ');
		while(command->cmd_ex[i])
		{
			printf("cmd[%i] = [%s]\n", i, command->cmd_ex[i]);
			i++;
		}
		command = command->next;
	}
	command = first_node;
	reset_datanode(first_node, data);
	// FONCTION $VAR a appli sur chaque node avant redir
	// ls < $USER
	// bash: bdewits: No such file or directory

	// FONCTION REDIR appli sur chaque node
	// a retest quand on aura free le pars et realloc les nodes
	while (command != NULL)
	{
		open_redir(command, -1, -1);
		command = command->next;
	}
	command = first_node;
}

void	reset_datanode(t_command *first_node, t_parser *data)
{
	data->command = first_node;
	data->head_cmd = first_node;
}

void	ft_parse_pipe(t_command *command)
{
	int	pos_pipe;

	pos_pipe = ft_strchr_pipe(command->line);
	printf("pos_pipe = %i\n", pos_pipe);
	if (pos_pipe == 0)
		return ;
	while (pos_pipe > 0)
	{
		command->next = ft_init_node();
		command->next->line = ft_strndup(command->line, pos_pipe + 1);
		command->line = ft_replace_line(command->line, pos_pipe);		
		command = command->next;
		pos_pipe = ft_strchr_pipe(command->line);
	}
}

# include "pars.h"


int	ft_check_pipe_after(char *line, int i)
{
	while(line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

int ft_check_pipe_empty(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '|')
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	while (line[i])
	{
		if (line[i] == '|')
		{
			if (line[i + 1] == '|')
				return (1);
			if (ft_check_pipe_after(line, i + 1) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_how_many_even_redir(char *line, int i)
{
	int	j;
	int	k;
	int start = 0;

	j = 0;
	k = 0;
	start = i;
	while (line[i] == '>')
		{
			i++;
			j++;
		}
	i = start;
	while (line[i] == '<')
	{
		i++;
		k++;
	}
	return (j + k);
}

int	ft_check_redir_after(char *line, int i)
{
	if (line[i] == '>' && line[i + 1] == '<')
		return (1);
	if (line[i] == '<' && line[i + 1] == '>')
		return (1);
	if (ft_how_many_even_redir(line, i) > 2)
		return (1);
	i++;
	while(line[i] && (line[i] == ' ' || line[i] == '\t'))
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
		if (line[i] == '>' && line[i + 1] == '>')
			return (1);
		if (line[i] == '>' && line[i + 1] == '>')
			return (1);
		i++;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

int ft_check_redir_empty(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '\0')
		return (1);
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '>' || line[i] == '<')
	{
		if (line[i] == '>' || line[i] == '<')
			return (1);
		i++;
	}
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (ft_check_redir_after(line, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_close_quote(char *line)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while(line[i])
	{
		if (line[i] == '\'' && !ft_is_between_d_quote(line, i))
			single_quote++;
		if (line[i] == '"' && !ft_is_between_s_quote(line, i))
			double_quote++;
		i++;
	}
	if (single_quote % 2 != 0)
		return (1);
	if (double_quote % 2 != 0)
		return (1);
	return (0);
}

// int main()
// {
// 	t_command	*command;

// 	command = ft_init_node();
// 	while (1)
// 	{
// 		command->line = readline("minishell> ");
// 		if (ft_strcmp(command->line, "exit") == 0)
// 		{
// 			free(command->line);
// 			return (1);
// 		}
// 		if (ft_check_pipe_empty(command->line) == 1 ||
// 				ft_check_redir_empty(command->line) == 1 ||
// 				ft_check_close_quote(command->line))
// 				// NEED TO CHECK IN CLOSE QUOTE IF THE ACTUAL QUOTE IS BETWEEN SIMPLE OR DOUBLE QUOTE AND NOTE INCREMENT
// 				// THE BEFORE AND AFTER FLAG 
// 				// FOR EXEMPLE : echo "'coucou" hello | wc '-l' should'nt an error syntax
// 		{
// 			printf("error syntax\n");
// 			free(command->line);
// 			continue ;
// 		}
// 		ft_parse_line(command);
// 		// open_redir(command);
// 		free(command->line);
// 	}
// 	return (0);
// }

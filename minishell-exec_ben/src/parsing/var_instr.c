#include "pars.h"

//FONCTION POUR LES $VAR
char	*ft_str_var(t_parser *data, char *str, char *cpy, int i)
{
	int	j;

	j = -1;
	cpy = (char *)malloc((sizeof (char)) * (1500));
	while (str[++i] != '\0')
	{
		if (str[i] == '\'')
			replace_cot(str, cpy, &j, &i); //simple '$USERS '
		else if (str[i] == '\"')
		{
			if (double_cot((str + i + 1), cpy, &j, data) == 1) //double "$USERS "
				while (str[++i] != '\"' && str[i] != '\0')
					;
		}
		else if (str[i] == '$' && str[i + 1] != '\0')
		{
			if (replace_var((str + i + 1), cpy, &j, data) == 1) //aucune $USERS 
				while (str[i] != ' ' && str[i] != '\0' && str[i] != '	')
					i++;
			cpy[++j] = str[i];
		}
		else
			cpy[++j] = str[i];
		if (!str[i])
			i--;
	}
	return (copie_final(str, cpy, &j));
}

char*	copie_final(char *str, char *cpy, int *j)
{
	cpy[++(*j)] = '\0';
	free(str);
	str = ft_strdup(cpy);
	free(cpy);
	return (str);
}

void	replace_cot(char *str, char *cpy, int *j, int *i)
{
	printf("replace_cot\n");
	cpy[++*j] = str[*i]; //copie la premiere
	while (str[(++*i)] != '\'' && str[(*i)] != '\0') // Copier tout entre les guillemets simples
		cpy[++(*j)] = str[(*i)];
	cpy[++(*j)] = str[(*i)]; // Fermer les guillemets
}

int	double_cot(char *str, char *cpy, int *j, t_parser *data)
{
	int	i;

	i = 0;
	printf("double cot\n");
	cpy[(++*j)] = '\"';
	while (str[i] != '\0' && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			replace_var((str + i + 1), cpy, j, data);
			while (str[i] != ' ' && str[i] != '	' && str[i] != '\0'
				&& str[i] != '\"')
				i++;
		}
		if (str[i] != '$')
			cpy[(++*j)] = str[i];
		i++;
	}
	cpy[(++*j)] = str[i];
	return (1);
}

int	replace_var(char *str, char *cpy, int *j, t_parser *data)
{
	int	i;
	int	l;

	i = 0;
	l = -1;
	while (str[i] != ' ' && str[i] != '\"' && str[i] != '\0')
		i++;
	if (i == 1 && str[i - 1] == '?')
		return (var_error(cpy, j, NULL, data), 1);
	while (data->envp[++l] != NULL)
	{
		if (compare_str(str, data->envp[l], i) == 0)
			break ;
	}
	if (data->envp[l] == NULL)
		return (1);//skip la var
	i = -1;
	if (data->envp[l] != NULL)
	{
		while (data->envp[l][++i] != '=')
			;
		while (data->envp[l][++i] != '\0')
			cpy[++(*j)] = data->envp[l][i];
	}
	return (1);
}

void	var_error(char *cpy, int *j, char *error, t_parser *data)
{
	int	i;

	i = 0;
	error = ft_itoa(WEXITSTATUS(data->status));
	while (error[i] != '\0')
	{
		cpy[++(*j)] = error[i];
		i++;
	}
	free(error);
}
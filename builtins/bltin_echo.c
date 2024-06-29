#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	escape_print(char c)
{
	if (c == 'n')
		printf("\n");
	else if (c == 't')
		printf("\t");
	else if (c == '\\')
		printf("\\");
	else if (c == '"')
		printf("\"");
	else if (c == '\'')
		printf("\'");
	else if (c == 'r')
		printf("\r");
	else if (c == 'b')
		printf("\b");
	else
		printf("\\%c", c);
}

void	print_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\\')
		{
			i++;
			escape_print(arg[i]);
		}
		else
			printf("%c", arg[i]);
		i++;
	}
}

void	bltin_echo(int argc, char **argv)
{
	int	i;
	int	new_line;

	i = 2;
	new_line = 1;
	if (strcmp(argv[2], "-n") == 0)
	{
		if (argc <= 3)
		{
			printf("need more args\n");
			return ;
		}
		new_line = 0;
		i = 3;
	}
	while (i < argc)
	{
		print_arg(argv[i]);
		i++;
		if (i < argc)
			printf(" ");
	}
	if (new_line == 1)
		printf("\n");
}

int	main(int argc, char **argv)
{
	if (argc <=2)
	{
		printf("need more args\n");
		return (0);
	}
	if (strcmp(argv[1], "echo") != 0)
	{
		printf("need 'echo' as 1st arg");
		return (0);
	}
	bltin_echo(argc, argv);
	return (0);
}

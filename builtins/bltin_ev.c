#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	bltin_env()
{
	extern char	**environ;
	char		**env;

	env = environ;
	while (*env != 0)
	{
		if (strncmp(*env, "_=", 2) == 0)
		{
			printf("_=/usr/bin/env\n");
			return ;
		}
		printf("%s\n", *env);
		env++;
	}
}

void	bltin_export(int argc, char **argv)
{
}

void	bltin_unset(int argc, char **argv)
{}

int	main(int argc, char **argv)
{
	if (strcmp(argv[1], "env") == 0)
		bltin_env();
	return (0);
}

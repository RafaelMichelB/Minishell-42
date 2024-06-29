#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void	bltin_pwd()
{
	size_t	size;
	char	*buffer;

	size = 1024;
	buffer = calloc(size, sizeof(char *));
	if (!buffer)
		return ;
	while (getcwd(buffer, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size *= 2;
			free(buffer);
			buffer = calloc(size, sizeof(char *));
			if (!buffer)
				return ;
		}
		else
		{
			free(buffer);
			return ;
		}
	}
	printf("%s\n", buffer);
	free(buffer);
}

int	main()
{
	bltin_pwd();
	return (0);
}

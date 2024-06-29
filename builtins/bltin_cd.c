#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void	bltin_cd(int argc, char **argv)
{
	if (argc > 3)
	{
		printf("bash : cd : trop d'arguments");
		return ;
	}
	if (argc == 2)
	{
		chdir(getenv("HOME"));
		return ;
	}
	if (access(argv[2], F_OK) == -1)
	{
		printf("bash : cd : %s : \
		Aucun fichier ou dossier de ce nom\n", argv[2]);
		return ;
	}
	if (chdir(argv[2]) != 0)
		perror("chdir ");
}

int	main(int argc, char **argv)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	bltin_cd(argc, argv);
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

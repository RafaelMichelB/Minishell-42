typedef struct s_nlist
{
	char     c;
	struct s_nlist *next;
} t_nlist;

typedef struct s_cmd
{
    char *path;
    char **args;
} t_cmd;
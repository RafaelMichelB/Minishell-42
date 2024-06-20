#define RED_IN 21
#define RED_OUT 22
#define RED_APP 23
#define CMD 1
#define END 3
#define NONE 4

typedef struct s_nlist
{
	char     c;
	struct s_nlist *next;
} t_nlist;

typedef struct s_cmd
{
	int	type;
	char	*path;
	char	**args;
} t_cmd;

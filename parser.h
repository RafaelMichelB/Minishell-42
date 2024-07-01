#define RED_IN 21
#define RED_OUT 22
#define RED_APP 23
#define CMD 1
#define END 3
#define NONE 4
#define HDOC 5
#define	BUILTIN 6

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

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
} t_env;

typedef struct s_data
{
	int		flag;
	int		status;
	struct s_env	*env;
} t_data;

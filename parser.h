#define RED_IN 21
#define RED_OUT 22
#define RED_APP 23
#define CMD 1
#define END 3
#define NONE 4
#define HDOC 5
#define	BUILTIN 6
#define ENDT 7

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

int     bltin_unset(t_cmd cmd, t_env **env);
char    *ft_getenv(char *s, t_env *env);
void    add_env_line(t_env **env, t_env *node);
t_env   *init_env_line(char *key, char *value);
char    *add_str(char *str, char *s2);
int     only_in(char *str, char c);
int	*find_hdocs(t_cmd *cmd, int n);
int	handle_hdocs(char *end_w, t_cmd *cmds, int j, t_env **env);
void	clear_cmds(t_cmd *cmds);
void	env_clear(t_env **env);
void	*sim_glob(char c, t_env **env, t_cmd *cmd, void *n);

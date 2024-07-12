#ifndef PARSER_H
# define PARSER_H
# define RED_IN 21
# define RED_OUT 22
# define RED_APP 23
# define CMD 1
# define END 3
# define NONE 4
# define HDOC 5
# define BUILTIN 6
# define ENDT 7
# define NOF ": No such file or directory"
# define IM 2147483647

# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "libft/libft.h"

typedef struct s_nlist
{
	char			c;
	struct s_nlist	*next;
}	t_nlist;

typedef struct s_cmd
{
	int		type;
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		simulpipe(t_cmd *cmd, t_env **env);
void	simulpipe2(int tab[], t_cmd *cmd, t_cmd **type);
t_cmd	*main3(t_list *t_lst[], t_nlist *lst, int *flag, t_env **env);
char	**gen_args(t_list **lst);
void	remove_env(t_env **env, char *str);
void	close_fds(int fd[]);
t_env	*change_env(char *s, t_env **env, char *s2);
int		count_size_args(char **arg);
int		bltin_unset(t_cmd cmd, t_env **env);
char	*ft_getenv(char *s, t_env *env);
void	add_env_line(t_env **env, t_env *node);
t_env	*init_env_line(char *key, char *value);
char	*add_str(char *str, char *s2);
int		only_in(char *str, char c);
int		*find_hdocs(t_cmd *cmd, int n);
int		handle_hdocs(char *end_w, t_cmd *cmds, int j, t_env **env);
void	clear_cmds(t_cmd *cmds);
void	env_clear(t_env **env);
void	*sim_glob(char c, t_env **env, t_cmd *cmd, void *n);
void	handle_sigint(int sig);
char	*add_str2(char *str, char **s);
char	*add_str(char *str, char *s);
int		is_in_str(char c, char *str);
char	*ft_strjoin3elem(char *s1, char *s2, char *s3);
char	**ft_split1(char *str, char c);
int		nlstsize(t_nlist *lst);
void	nlstclear(t_nlist **lst);
t_nlist	*nlst_new(char c);
t_nlist	*nstlast(t_nlist *lst);
void	nlstadd_back(t_nlist **lst, t_nlist *new);
t_nlist	*create_stack_1(char *str);
char	*join_stack(t_nlist *stack);
void	create_stack32(t_nlist **stack1, t_nlist **stack2, \
t_list **stack3, char **s);
void	create_stack33(t_nlist **stack1, t_nlist **stack2);
void	create_stack34(t_nlist **stack1, t_nlist **stack2);
void	create_stack35(t_nlist **stack1, t_nlist **stack2, \
t_list **stack3, char **s);
void	create_stack36(t_nlist **stack1, t_nlist **stack2);
void	create_stack37(t_nlist **stack2, t_list **stack3, char **s);
t_list	*create_stack3(t_nlist *stack1);
void	iq42(t_nlist *stacks[], char *strs[], int flag);
void	iq4(t_nlist *stacks[], char *strs[], int flag, t_env *env);
void	iq322(t_nlist *stacks[], char *strs[], int flag, t_env *env);
void	iq32(t_nlist *stacks[], char *strs[], int flag, t_env *env);
void	iq3(t_nlist *stacks[], char *strs[], int flag, t_env *env);
void	iq2(t_nlist *stacks[], char *strs[]);
void	iq12(t_nlist *stacks[], char *strs[], int flag, t_env *env);
t_list	*interpret_quotes(t_list *lst, int flag, t_env *env);
void	ca22(t_list **l, int *i, t_cmd **cmd_array);
void	ca23(t_list **l, int *i, t_cmd **cmd_array);
void	ca22(t_list **l, int *i, t_cmd **cmd_array);
void	ca23(t_list **l, int *i, t_cmd **cmd_array);
void	ft_del(void	*content);
char	**find_all_path(char **var_env);
char	*find_nice_path(char *cmd, char **env);
int		only_in(char *str, char c);
int		only_in2(char *str, char c, char c2);
void	ca2(t_list **l, int *i, t_cmd **cmd_array, t_env *env);
void	ca32(t_list **l, int *i, t_cmd **cmd_array, int *j);
int		ca3(t_list **l, int tab[], t_cmd **cmd_array);
t_cmd	*create_args(t_list *l, t_env *env);
void	do1cmd2(int fd[], int *i, t_cmd *cmds);
void	do1cmd3(int fd[], int *i, t_cmd *cmds);
int		do1cmd41(t_cmd *cmds, t_cmd *cmd, int i, char **env);
int		do1cmd42(t_cmd *cmds, t_cmd *cmd, int i, char **env);
int		do1cmd43(t_cmd *cmds, t_cmd *cmd, int i, char **env);
int		do1cmd(t_cmd *cmds, char **env, t_cmd *cmd, int i);
int		do1cmd5(t_cmd *cmd, t_cmd *cmds, char **env, int fd[]);
void	do1cmd32(int fd[], int *i, t_cmd *cmds);
int		do1cmd45(t_cmd *cmds, t_cmd *cmd, int j, char **env);
int		do1cmd44(t_cmd *cmds, t_cmd *cmd, int j, char **env);
void	change_st2(char **str, char ***tab, int flags[]);
void	change_st(char **tab, int f[]);
char	**convert_array(t_env *env);
t_env	*init_env_line(char *key, char *value);
t_env	*envlast(t_env *lst);
void	add_env_line(t_env **env, t_env *node);
void	env_clear(t_env **env);
t_env	*generate_env(char **env);
t_env	*generate_env2(char **env);
int		envsize(t_env *env);
int		abs(int i);
int		in_env(t_env *env, char *s);
char	*ft_strtrim2(char const *s1, char const *set);
t_env	*order_env(t_env *env);
void	handle_sigint2(int sig);
void	clear_cmds(t_cmd *cmds);
int		detect_builtin(char *str);
t_cmd	handle_hdoc2(t_list **l, t_env *menv);
t_cmd	handle_hdoc(t_list **l, t_env *menv);
int		find_hdoc2(t_cmd *cmd);
void	apply_flags(t_list *t_lst, int flags[]);
t_list	*lstdup(t_list *lst);
void	open_fds(int fd);
int		bltin_cd(t_cmd cmd, t_env *env);
int		cd2(t_cmd *cmd, int i[]);
void	cd3(t_env **env, char *str[], char cwd[], int fd[]);
int		builtin_cd_prep(t_cmd *cmd, t_env **env);
void	escape_print(char c, int fd);
void	print_arg(char *arg, int fd);
void	bltin_echo(t_cmd cmd, int fd);
int		builtin_echo_prep(t_cmd *cmd);
int		bltin_pwd(int fd);
int		builtin_pwd_prep(t_cmd *cmd);
void	free_unset(t_env *tc);
int		bltin_unset(t_cmd cmd, t_env **env);
int		builtin_unset_prep(t_cmd *cmd, t_env **env);
int		bltin_env(t_env *env, int fd);
int		builtin_env_prep(t_cmd *cmd, t_env **env);
int		bltin_export2(t_cmd cmd, t_env **env, int size);
int		ex2(t_env *cp, int fd);
int		bltin_export(t_cmd cmd, t_env **env, int fd);
int		builtin_export_prep(t_cmd *cmd, t_env **env);
void	main4(char *str, char **tab, int flags[]);
void	main2(char *str, t_env **env, int *flag, int fd);
void	handle_sigint(int sig);
void	main12(char *str, t_env **my_env, int flag);
void	main13(char ***t, int flag, char *str, t_env **my_env);
int		handle_hdocs(char *end_w, t_cmd *cmds, int j, t_env **env);
int		*find_hdocs(t_cmd *cmd, int n);
void	ca26(t_list **l, t_env **env, t_cmd **cmd_array, int *i);
void	handle_sigint3(int sig);
int		cd2(t_cmd *cmd, int i[]);
void	handle_sigint4(int sig);
void	hd2(char **arr, t_cmd *cmds, int j, char *end_w);
void	dc(int fd[], int *i, t_cmd *cmds);

#endif

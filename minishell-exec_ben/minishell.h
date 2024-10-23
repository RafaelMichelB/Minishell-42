/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-wits <bde-wits@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:27:28 by bde-wits          #+#    #+#             */
/*   Updated: 2024/10/17 10:27:28 by bde-wits         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "pars.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_command	t_command;

typedef struct s_parser
{
	char			**envp; //contient l'env parent
	char			**tab_path;//dois contenir les chemins d'access cmd
	char			*validpath;
	int				**pipefd;//entre sortie standard
	int				status;
	int				index;//pos list
	int				size_li;//len de la list cmd
	int				cmd_builtin;//cmd builtin sans fork
	int				handle_error;//printf le return d'erreur en cas de echo $?
	int				ipid;
	//env ici sa peut pose des problemes peu etre dans l'execution ?
	//t_command temp first node , pour pouvoir free a la fin
	// t_command_table	*command_table;
	t_command		*head_cmd;
	t_command		*command;
}	t_parser;

typedef struct s_command
{
	char				*line;
	char				**cmd_ex;
	int					fd_in;//exec entre
	int					fd_out;//exec sortie
	int					flags;//flag heredoc need unlink;
	struct s_command	*next;
}				t_command;

int					compare_str(const char *s1, const char *s2, int n);

// utils/get_str_len.c
int					get_str_len(char *str);

// utils/duplicate_str.c
char				*duplicate_str(char *s);

// utils/join.c
char				*join_str(char **table, char c);

// utils/split.c
char				**split_str(char const *s, char c);
void				free_split_str(char **words);

// parser/command.c

// parser/parser.c

//exec/hub_exec.c/init
void				hub_exec(t_parser *data);
int					init_ex_utils(t_parser *data);
void				init_envp(t_parser *data, char **env);
int					init_pipe(t_parser *data, int i);

// //exec/hub_exec/exec

int					exec(t_parser *data, pid_t *pid);
int					children(t_parser *data);
void				init_cmdtab(t_parser *data);
char				*joinspace(char *s1, char *s2);
int					pipe_redir(t_parser *data);
void				close_pipe(t_parser *data);
char				**finding_path(t_parser *data);
char				*checkaccess(char *cmd, char **split_path);
void				freetab_path(t_parser *data);
char				*ft_strjoin(char *s1, char *s2, int slash);
char				*ft_strjoinslash(char *s1, char *s2);
int					ft_size(t_command **li);
void				set_error(t_parser *data, int code);
void				close_pipe_child(t_parser *data);
int					compare(const char *s1, const char *s2);
int					redir_out(t_parser *data);

int					cmd_builtin(t_parser *data, pid_t *pid);//exec//cmd_builtin
int					ms_env(t_parser *data, pid_t *pid, int i);
int					ms_pwd(t_parser *data, pid_t *pid);
int					ms_cd(t_parser *data);/*, pid_t *pid*/
void				ms_export(t_parser *data, int i);
int					verif_argexport(char *arg, int i, t_parser *data);
void				printexport(t_parser *data, int i, int sign);
void				setvar(t_parser *data, char *str);
void				modif_var(t_parser *data, char *val, int i);
char				**suprlineenvp(t_parser *data, int i);/* int sign, */
int					ms_unset(t_parser *data, int i, int j);
int					search_var(char *search, char *senvp);
char				**tri_ex(t_parser *data, int i, int j, char **cpy);
void				bubble_sort(char **array);
int					ms_exit(t_parser *data, int i, int er);
int					return_to_ex(t_parser *data);
void				free_ex(t_parser *data);
void				free_all(t_parser *data);
void				ms_echo(t_parser *data, int i, int in, int out);
void				redir_echo(t_parser *data);
int					check_arg(t_parser *data, char *str, int i);

// char				*ft_itoa(int n);
// int					get_dec(int n);
// void				var_error(char *cpy, int *j, char *error, t_parser *data);
// char				*str_var(t_parser *data, char *str, char *cpy, int i);
// void				replace_cot(char *str, char *cpy, int *j, int *i);
// int					double_cot(char *str, char *cpy, int *j, t_parser *data);
// int					replace_var(char *str, char *cpy, int *j, t_parser *data);
// void				copie_final(char *str, char *cpy, int *j);

// // free list fonctionne avec erreur
void				free_parser(t_parser *data, int i);
void				free_command(t_parser *data);
void				free_insidenode(t_command *cmd);

// //utils/ex
int					ft_strncmp(char *str, int n);
//char				*ft_strdup(char *s);
int					ft_strlen(char *str);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(char *ptr);

int					heredoc(t_command *node, int i);
#endif

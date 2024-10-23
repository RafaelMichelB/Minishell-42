#ifndef	PARS_H
# define PARS_H

typedef struct s_command t_command;
typedef struct s_parser t_parser;

# include "minishell.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// typedef struct s_command
// {
// 	char	*line;
// 	char	**cmd_ex;
// 	int		fd_in;//exec entre
// 	int		fd_out;//exec sortie
	
// 	struct s_command	*next;
// }				t_command;

	// t_command	*first_node;



// /////////////////  pars  ///////////////// //

int 		ft_check_pipe_empty(char *line);
int			ft_check_pipe_after(char *line, int i);
int			ft_check_redir_after(char *line, int i);
int 		ft_check_redir_empty(char *line);
int			ft_check_close_quote(char *line);
int			ft_how_many_even_redir(char *line, int i);

// /////////////////  split_to_tab  ///////////////// //

int			ft_nb_array(char *line);
char		*ft_replace_line(char *line, int pos_pipe);
t_command	*ft_split_line_to_cmd(t_command *command);


// /////////////////  utils  ///////////////// //

int			ft_strcmp(const char *s1, const char *s2);
int			ft_strchr(const char *s, int c);
char		*ft_strndup(const char *s, int i);
char		*ft_strdup(char *s);
int			ft_lenn(const char *str, int n);

// /////////////////  init  ///////////////// //;

t_command	*ft_init_node(void);

// /////////////////  quote  ///////////////// //

int			ft_is_between_s_quote(char *str, int i);
int			ft_is_between_d_quote(char *str, int i);
int			ft_is_between_quote(char *str, int i);

// /////////////////  split  ///////////////// //

char		**ft_split_of_the_death(char const *s, char c);
char		**ft_free_all(char **str, int j);
int			ft_countword(char const *str, char c);
int			ft_lenword(char const *str, char c);

// /////////////////  utils2  ///////////////// //

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t n, size_t size);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// /////////////////  pipe  ///////////////// //

int			ft_strchr_pipe(char *str);
void		ft_parse_line(t_command *command, t_parser *data);
void		ft_parse_pipe(t_command *command);

// ///////////////// A TRIE ///////////////// //

void    	open_redir(t_command *node, int i, int fd);
void 		handle_output(t_command *command, int i, int fd);
void		supr_redir(t_command *node, int i, int pos);
char		**suprin_tab(char **tab, int i, int pos);
int			verif_parse(char *line);//in main
int			ft_is_redir(char c);
void		reset_datanode(t_command *first_node, t_parser *data);

//////////////////////////////////////////

char				*ft_itoa(int n);
int					get_dec(int n);
void				var_error(char *cpy, int *j, char *error, t_parser *data);
char				*ft_str_var(t_parser *data, char *str, char *cpy, int i);
void				replace_cot(char *str, char *cpy, int *j, int *i);
int					double_cot(char *str, char *cpy, int *j, t_parser *data);
int					replace_var(char *str, char *cpy, int *j, t_parser *data);
char*				copie_final(char *str, char *cpy, int *j);

int	ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);

#endif
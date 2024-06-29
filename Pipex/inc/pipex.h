/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:11:24 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/17 21:11:26 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

/* pipex.c */
int		ft_exec(char *arg, char **envp);
void	child_process(char **argv, int *p_fd, char **envp);
void	parent_process(char **argv, int *p_fd, char **envp);

/* utils.c */
void	ft_exit(int i);
char	**get_paths(char **envp);
char	*get_full_path(char *path, char *cmd);

#endif

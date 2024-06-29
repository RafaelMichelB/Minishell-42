/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 21:11:37 by dbonali           #+#    #+#             */
/*   Updated: 2024/06/17 21:11:39 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
# include "pipex.h"
# include "../libft/get_next_line.h"

/* pipex_bonus.c */
int		check_last_arg(char *argv, char **envp);

/* mains_bonus.c */
void	do_pipe(char *arg, char **envp);
int		pipex_main(int argc, char **argv, char **envp);
int		hdoc_main(int last, int argc, char **argv, char **envp);
void	hdoc_input(char **argv, int *p_fd);
int		no_file2_main(int argc, char **argv, char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbonali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:57:20 by dbonali           #+#    #+#             */
/*   Updated: 2024/03/21 22:57:26 by dbonali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*read_and_stash(int fd, char *stash);
char	*extract_line(char *stash, char *line);
char	*clean_stash(char *stash);
int		found_new_line(char *stash);
char	*ft_strjoin(char *stash, char *buff);
char	*ft_strdup(char *str);
char	*ft_strcpycat(char *stash, char *temp, char *buff);
int		ft_strlen(const char *str);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmichel- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:55:28 by rmichel-          #+#    #+#             */
/*   Updated: 2023/10/28 21:48:16 by rmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

char	*get_next_line(int fd);
char	*gnl2(int fd, char *buff_temp, char *line, char **buffer);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*check_special(int *pos, char **buffer);
void	*ft_callocg(size_t nmemb);
char	*ft_strdupg(const char *s);
char	*add_buffer(char *line, char **buff, int len);
void	*ft_memcpyg(void *dest, const void *src, size_t n);

#endif

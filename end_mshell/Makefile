# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 16:47:00 by rmichel-          #+#    #+#              #
#    Updated: 2024/07/16 18:01:10 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBNAME = libft/libft.a
SRCS = blt_cd.c      change_lst.c    env1.c      parse_copy.c  sp2.c     utils.c \
blt_echo.c    change_str.c    env2.c      parsing1.c    utils2.c \
blt_env.c     create_args1.c  gen_args.c  parsing2.c    utils3.c \
blt_export.c  create_args2.c  heredoc.c   parsing3.c    utils4.c \
blt_pwd.c     docmds1.c       mains.c     parsing4.c    utils5.c \
blt_unset.c   docmds2.c       nlst.c      sp1.c         utils6.c utils7.c utils8.c

OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)

lib : 
	$(MAKE) -C libft all bonus

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(NAME) : $(OBJ) lib
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBNAME) -lreadline

bonus : all

clean : 
	rm -rf $(OBJ)
	$(MAKE) -C libft clean

fclean : clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re : fclean $(NAME)

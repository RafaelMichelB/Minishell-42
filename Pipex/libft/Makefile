# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbonali <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 20:01:28 by dbonali           #+#    #+#              #
#    Updated: 2024/06/17 21:45:03 by dbonali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_isalnum.c ft_strlen.c ft_tolower.c \
				ft_toupper.c ft_bzero.c ft_memset.c ft_memcpy.c \
				ft_memcmp.c ft_memchr.c ft_memmove.c \
				ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_calloc.c ft_strlcpy.c ft_strlcat.c \
				ft_strchr.c ft_strdup.c ft_substr.c \
				ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c \
				ft_putendl_fd.c ft_strtrim.c ft_strjoin.c \
				ft_atoi.c ft_itoa.c ft_split.c ft_striteri.c \
				ft_strmapi.c ft_printf_utils.c ft_printf.c \
				get_next_line_utils.c get_next_line.c	

SRCS_BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
			ft_lstiter.c ft_lstmap.c

OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

CC		= gcc

CFLAGS		= -Wall -Wextra -Werror

RM		= rm -rf

NAME		= libft.a

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

bonus :		$(OBJS_BONUS)
			ar rcs $(NAME) $(OBJS_BONUS)

all :		$(NAME)

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all bonus clean fclean re

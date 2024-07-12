NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isdigit.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_isalpha.c \
		ft_memset.c \
		ft_atoi.c \
		ft_memmove.c \
		ft_bzero.c \
		ft_strmapi.c \
		ft_calloc.c \
		ft_putchar_fd.c \
		ft_isalnum.c \
		ft_strncmp.c \
		ft_putendl_fd.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strtrim.c \
		ft_strchr.c \
		ft_substr.c \
		ft_strdup.c \
		ft_tolower.c \
		ft_itoa.c \
		ft_striteri.c \
		ft_toupper.c \
		ft_memchr.c \
		ft_strlcat.c \
		ft_strjoin.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_strlcpy.c \
		ft_putnbr_fd.c \
		printf/ft_count_percent.c \
		printf/ft_del.c \
		printf/ft_new_node.c \
		printf/ft_printf.c \
		printf/ft_ptoa.c \
		printf/ft_putlst.c \
		printf/ft_preput.c \
		printf/ft_utoa.c \
		printf/ft_xtoa_caps.c \
		printf/ft_xtoa.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c
		


SRCS_BONUS = ft_lstadd_back_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstnew_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c 

OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus : $(OBJ_BONUS)
	ar rc $(NAME) $(OBJ_BONUS)

clean : 
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)


NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

SOURCE = pars.c utils.c split_to_tab.c quote.c init.c split.c pipe.c utils2.c

OBJS = $(SOURCE:.c=.o)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

all: $(NAME)

clean :
		rm -f $(OBJS)

fclean: clean
		    rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
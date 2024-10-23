NAME = minishell

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LFLAGS = -lreadline

INC_PATH = .
SRC_PATH = ./src/
OBJ_PATH = ./obj/
OBJ_FOLD = utils builtins parsing exec

SRC_FILES = minishell.c \
	utils/compare_str.c \
	utils/get_str_len.c \
	utils/duplicate_str.c \
	utils/join_str.c \
	utils/split_str.c \
	utils/utils_ex.c\
\
	parsing/pars.c \
	parsing/init.c \
	parsing/pipe.c \
	parsing/quote.c \
	parsing/split.c \
	parsing/split_to_tab.c \
	parsing/utils.c \
	parsing/utils2.c \
	parsing/open.c \
	parsing/var_instr.c \
\
	exec/hub_exec.c \
	exec/children_utils.c\
	exec/free1.c \
	exec/init_ex.c \
	exec/ft_strjoin.c \
	exec/pipe_ex.c \
	exec/str_len.c \
	exec/utils_ex1.c \
	exec/utils_ex2.c \
\
	builtins/ms_cd.c \
	builtins/ms_echo.c \
	builtins/ms_env.c \
	builtins/ms_exit.c \
	builtins/ms_export.c \
	builtins/ms_export2.c \
	builtins/ms_pwd.c \
	builtins/ms_unset.c \
\
	parsing/ft_lstadd_back_bonus.c \
	parsing/ft_lstadd_front_bonus.c \
	parsing/ft_lstclear_bonus.c \
	parsing/ft_lstdelone_bonus.c \
	parsing/ft_lstlast_bonus.c \
	parsing/ft_lstnew_bonus.c \
	parsing/ft_lstsize_bonus.c \

LIBS = $(addprefix $(LIB_PATH),$(LIB_NAME))
SRCS = $(addprefix $(SRC_PATH),$(SRC_FILES))
OBJS = $(addprefix $(OBJ_PATH),$(SRC_FILES:.c=.o))
OBJS_FOLD = $(addprefix $(OBJ_PATH),$(OBJ_FOLD))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) -I $(INC_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	$(CC) -o $@ -c $< $(CFLAGS) -I $(INC_PATH)
$(OBJ_PATH) : | $(OBJS_FOLD)
	mkdir -p $(OBJ_PATH)
$(OBJS_FOLD) :
	mkdir -p $(OBJS_FOLD)

fclean : clean
	rm -rf $(NAME)
clean :
	rm -rf $(OBJ_PATH)


re : fclean all

.PHONY : all bonus fclean clean re

#\
	exec/str_dup.c \
	exec/signal.c \
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbonali <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 13:39:43 by dbonali           #+#    #+#              #
#    Updated: 2024/06/19 13:39:44 by dbonali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a
NAME = pipex

# **************************************************************************** #
#                                   FILES                                      #
# **************************************************************************** #

MAIN = main.c
SRC = pipex.c \
      utils.c \

MAIN_BONUS = main_bonus.c
SRC_BONUS = mains_bonus.c \
	    pipex_bonus.c \

# **************************************************************************** #
#                                   PATH                                       #
# **************************************************************************** #

SRC_DIR = src/
SRC_BONUS_DIR = bonus/
OBJ_DIR = obj/
OBJ_DIR_BONUS = obj_bonus/
INCLUDE_DIR	= inc/

SRCS		= $(addprefix $(SRC_DIR), $(SRC))
OBJ 		= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ))

SRCS_BONUS	= $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS))
OBJ_BONUS 	= $(SRC_BONUS:.c=.o)
OBJS_BONUS	= $(addprefix $(OBJ_DIR_BONUS), $(OBJ_BONUS))

OBJ_MAIN  	= $(MAIN:.c=.o)
OBJS_MAIN	= $(addprefix $(OBJ_DIR), $(OBJ_MAIN))

OBJ_MAIN_BONUS	= $(MAIN_BONUS:.c=.o)
OBJS_MAIN_BONUS	= $(addprefix $(OBJ_DIR_BONUS), $(OBJ_MAIN_BONUS))

# **************************************************************************** #
#                                   COLOURS                                    #
# **************************************************************************** #

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m
ORANGE = \033[93m
BLUE = \033[94m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all : $(NAME)

bonus : $(OBJS) $(OBJS_BONUS) $(OBJS_MAIN_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $(NAME) $(OBJS) $(OBJS_BONUS) $(OBJS_MAIN_BONUS) $(LIBFT)
	@echo "\n"
	@echo "🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳"
	@echo "$(BOLD)$(GREEN)🥳        bonus fully compiled, ready to use        🥳$(RESET)"
	@echo "🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳"
	@echo "\n"

$(LIBFT):
	$(MAKE) -C libft all bonus

$(NAME): $(OBJS) $(OBJS_MAIN) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $@ $(OBJS) $(OBJS_MAIN) $(LIBFT)
	@echo "\n"
	@echo "🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳"
	@echo "$(BOLD)$(GREEN)🥳        pipex fully compiled, ready to use        🥳$(RESET)"
	@echo "🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳"
	@echo "\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@${CC} ${CFLAGS} -c $< -o $@ -I $(INCLUDE_DIR)

$(OBJ_DIR)%.o: $(MAIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS): $(OBJS) $(OBJS_BONUS) $(OBJS_MAIN_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -o $@ $(OBJS) $(OBJS_BONUS) $(OBJS_MAIN_BONUS) $(LIBFT)
	@echo "\n"
	@echo "🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳"
	@echo "$(BOLD)$(GREEN)🥳        bonus fully compiled, ready to use        🥳$(RESET)"
	@echo "🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳🥳"
	@echo "\n"

$(OBJ_DIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(OBJ_DIR_BONUS)
	@${CC} ${CFLAGS} -c $< -o $@ -I $(INCLUDE_DIR)

$(OBJ_DIR_BONUS)%.o: $(MAIN_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	@$(RM) $(OBJ_DIR)
	@$(RM) $(OBJ_DIR_BONUS)
	@$(RM) $(OBJ_BONUS)
	@make clean -C ./libft

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)
	@echo "\n"
	@echo "$(BOLD)$(BLUE)------------------------------------$(RESET)"
	@echo "$(BOLD)$(ORANGE)🌀          pipex cleaned         🌀$(RESET)"
	@echo "$(BOLD)$(BLUE)------------------------------------$(RESET)"
	@echo "\n"


re : fclean all

.PHONY: all bonus clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 14:39:51 by thle              #+#    #+#              #
#    Updated: 2023/01/19 11:17:45 by ccariou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror

NAME = corewar
ASM = asm

INCLUDES_DIR = ./includes/
OBJS_DIR = ./objs/

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

COREWAR_FILES = corewar.c
COREWAR_SRCS_DIR = ./srcs/corewar/
COREWAR_SRCS = $(addprefix $(COREWAR_SRCS_DIR), $(COREWAR_FILES))
COREWAR_OBJS = $(addprefix $(OBJS_DIR), $(COREWAR_FILES:%.c=%.o))

ASM_FILES = debug.c asm.c free_tools.c hash_tools.c label_tools.c \
						statement_tools.c read.c op_tools.c parse.c \
						write.c ft_atoi_base.c
ASM_SRCS_DIR = ./srcs/asm/
ASM_SRCS = $(addprefix $(ASM_SRCS_DIR), $(ASM_FILES))
ASM_OBJS = $(addprefix $(OBJS_DIR), $(ASM_FILES:%.c=%.o))

all: $(NAME) $(ASM)

$(NAME): $(LIB) $(OBJS_DIR) $(COREWAR_OBJS)
	@$(CC) -o $(NAME) $(FLAGS) $(COREWAR_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(NAME)"

$(ASM): $(LIB) $(OBJS_DIR) $(ASM_OBJS)
	@$(CC) -o $(ASM) $(FLAGS) $(ASM_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(ASM)"

$(LIB):
	@$(MAKE) -sC ./libft
	@echo "Compiled $(LIB)"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(COREWAR_SRCS_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(ASM_SRCS_DIR)%.c
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

clean:
	@$(MAKE) -sC $(LIB_DIR) clean
	@/bin/rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(NAME) $(ASM)

re: fclean all

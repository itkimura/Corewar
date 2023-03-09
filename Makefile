# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thle <thle@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 14:39:51 by thle              #+#    #+#              #
#    Updated: 2023/02/26 13:20:06 by itkimura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
DFLAGS  = -fsanitize=address -fsanitize=undefined \
	-fno-sanitize-recover=all -fno-sanitize=null -fno-sanitize=alignment

NAME = corewar
ASM = asm

INCLUDES_DIR = ./includes/
OBJS_DIR = ./objs/

LIB_DIR = ./libft/
LIB = $(addprefix $(LIB_DIR), libft.a)
LIB_INCLUDE = ./libft/includes/

COREWAR_FILES =		corewar.c				print.c					\
					validate_champion.c		init_structures.c		\
					update_players_array.c	free.c					\
					utils.c					run_game.c				
COREWAR_SRCS_DIR = ./srcs/corewar/
COREWAR_SRCS = $(addprefix $(COREWAR_SRCS_DIR), $(COREWAR_FILES))
COREWAR_OBJS = $(addprefix $(OBJS_DIR), $(COREWAR_FILES:%.c=%.o))


OP_FILES =	op_live.c op_ld.c op_st.c op_add.c op_sub.c op_and.c \
			op_or.c op_xor.c op_zjmp.c op_ldi.c op_sti.c op_fork.c \
			op_lld.c op_lldi.c op_lfork.c op_aff.c \
			op_utils.c get_arg.c get_value.c op.c place_value.c
OP_SRCS_DIR = ./srcs/corewar/operations/
OP_SRCS = $(addprefix $(OP_SRCS_DIR), $(OP_FILES))
OP_OBJS = $(addprefix $(OBJS_DIR), $(OP_FILES:%.c=%.o))

FLAG_FILES =		print_flag.c			print_flag_v.c			\
					flag.c					flag_validate_utils.c	\
					flag_validate.c			flag_v_validate.c
FLAG_SRCS_DIR = ./srcs/corewar/flags/
FLAG_SRCS = $(addprefix $(FLAG_SRCS_DIR), $(FLAG_FILES))
FLAG_OBJS = $(addprefix $(OBJS_DIR), $(FLAG_FILES:%.c=%.o))

ASM_FILES = debug.c asm.c free_tools.c hash_tools.c label_tools.c \
						statement_tools.c read.c op_tools.c parse.c \
						write.c write_util.c write_util2.c ft_atoi_base.c
ASM_SRCS_DIR = ./srcs/asm/
ASM_SRCS = $(addprefix $(ASM_SRCS_DIR), $(ASM_FILES))
ASM_OBJS = $(addprefix $(OBJS_DIR), $(ASM_FILES:%.c=%.o))

all: $(NAME) $(ASM)

debug: FLAGS += $(DFLAGS)
debug: all

$(NAME): $(LIB) $(COREWAR_OBJS) $(OP_OBJS) $(FLAG_OBJS)
	@$(CC) -o $(NAME) $(FLAGS) $(COREWAR_OBJS) $(OP_OBJS) $(FLAG_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(NAME)"

$(ASM): $(LIB) $(ASM_OBJS)
	@$(CC) -o $(ASM) $(FLAGS) $(ASM_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled $(ASM)"

$(LIB):
	@$(MAKE) -sC ./libft
	@echo "Compiled $(LIB)"

# $(OBJS_DIR):
# 	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(COREWAR_SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(ASM_SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(OP_SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

$(OBJS_DIR)%.o: $(FLAG_SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(FLAGS) -I$(INCLUDES_DIR) -I$(LIB_INCLUDE) -c $^ -o $@
	@echo "Compiled $@"

clean:
	@$(MAKE) -sC $(LIB_DIR) clean
	@/bin/rm -rf $(OBJS_DIR)

fclean: clean
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -f $(NAME) $(ASM)

re: fclean all

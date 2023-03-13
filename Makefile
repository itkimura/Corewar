# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 14:39:51 by thle              #+#    #+#              #
#    Updated: 2023/03/13 11:37:54 by itkimura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -g -Wall -Wextra -Werror

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
						write.c write_util.c write_util2.c ft_atoi_base.c \
						check_util.c
ASM_SRCS_DIR = ./srcs/asm/
ASM_SRCS = $(addprefix $(ASM_SRCS_DIR), $(ASM_FILES))
ASM_OBJS = $(addprefix $(OBJS_DIR), $(ASM_FILES:%.c=%.o))

# COLORS
GREEN			:= $(shell tput -Txterm setaf 2)
YELLOW			:= $(shell tput -Txterm setaf 3)
WHITE			:= $(shell tput -Txterm setaf 7)
RESET			:= $(shell tput -Txterm sgr0)
BOLD			:= $(shell tput bold)

all: $(NAME) $(ASM)

libft: $(LIB)

$(NAME): $(LIB) $(COREWAR_OBJS) $(OP_OBJS) $(FLAG_OBJS)
	@$(CC) -o $(NAME) $(FLAGS) $(COREWAR_OBJS) \
		$(OP_OBJS) $(FLAG_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled ${BOLD}$(NAME)${RESET}"

$(ASM): $(LIB) $(ASM_OBJS)
	@$(CC) -o $(ASM) $(FLAGS) $(ASM_OBJS) -L$(LIB_DIR) -lft
	@echo "Compiled ${BOLD}$(ASM)${RESET}"

$(LIB):
	@$(MAKE) -sC ./libft
	@echo "Compiled ${BOLD}$(LIB)${RESET}"

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
	@echo "Deleted ${BOLD}$(OBJS_DIR)${RESET}"

fclean:
	@$(MAKE) -sC $(LIB_DIR) fclean
	@/bin/rm -rf $(OBJS_DIR)
	@/bin/rm -f $(NAME) $(ASM)
	@echo "Deleted ${BOLD}$(NAME)${RESET}"
	@echo "Deleted ${BOLD}$(ASM)${RESET}"

re: fclean all


help:
	@echo "Usage: ${GREEN}make${RESET} ${BOLD}command${RESET} [options]\n"
	@echo "Commands:\n"
	@echo "  ${BOLD}make${RESET}\t\t\tcompile libft, asm and corewar"
	@echo "  ${BOLD}make libft${RESET}\t\tcompile ./libft/libft.a"
	@echo "  ${BOLD}make corewar${RESET}\t\tcompile corewar"
	@echo "  ${BOLD}make asm${RESET}\t\tcompile asm"
	@echo "  ${BOLD}make clean${RESET}\t\tdelete object files"
	@echo "  ${BOLD}make fclean${RESET}\c"
	@echo "\t\tdelete object files and all excutable files\c"
	@echo "(libft, push_swap and checker)"
	@echo "  ${BOLD}make re${RESET}\c"
	@echo "\t\tdelete object files and\c"
	@echo "all excutable files and compile all again"
	@echo "  ${BOLD}help${RESET}\t\t\tprint this help message\n"

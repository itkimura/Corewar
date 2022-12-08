# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 12:39:13 by leotran           #+#    #+#              #
#    Updated: 2022/11/20 23:58:26 by leo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	asm
LIBFT		=	libft/libft.a
# FLAGS		=	-Wall -Wextra -Werror -O3 -I. -Iincludes/
FLAGS = -I. -Iincludes/

LIBFT_DIR	=	libft/

SRCS = main.c

# CHK_SRCS	=	$(addprefix $(CHK_DIR), $(CHK_SRC))

OBJ_DIR		=	obj/
# OBJS		= 	$(CHK_OBJS) $(PS_OBJS) $(COMMON_OBJS)
# CHK_OBJS	=	$(patsubst %, $(OBJ_DIR)%, $(CHK_SRC:.c=.o))

all: $(NAME) main.c

$(NAME): $(LIBFT)  #$(CHK_OBJS) $(PS_OBJS) $(COMMON_OBJS)
	@gcc $(FLAGS) $(LIBFT) $(SRCS) -o $(NAME)
	@printf "Compilation complete.\n"
	
$(LIBFT):
	@make -C $(LIBFT_DIR)

# $(OBJ_DIR):
# 	@mkdir -p $(OBJ_DIR)

# $(OBJ_DIR)%.o: $(CHK_DIR)%.c
# 	@gcc $(FLAGS) -o $@ -c $<
# 	@printf "Checker compiled.\n"

clean:
	@make -C $(LIBFT_DIR) clean
	
# @rm -rf $(OBJS) $(SURPL_O)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all
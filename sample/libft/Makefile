# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leo <leo@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/20 12:39:13 by leotran           #+#    #+#              #
#    Updated: 2022/11/20 23:57:01 by leo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
FLAGS		=	-Wall -Wextra -Werror -O3 -I. -Iincludes/

LIBFT_SRC	=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c \
				ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c ft_putendl.c \
				ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c ft_strcat.c ft_strchr.c ft_strclr.c \
				ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
				ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
				ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
				ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
				ft_lstadd.c ft_lstiter.c ft_lstaddend.c ft_lstdelend.c \
				ft_lstsize.c ft_dlstnew.c ft_dlstaddfront.c ft_dlstaddend.c ft_dlstdelfront.c ft_countstrings.c \
				ft_strccpy.c ft_get_next_line.c ft_foreach.c ft_uitoa_base.c ft_putaddr.c ft_put_u_nbr.c \
				ft_uint_base_count.c ft_int_base_count.c ft_itoa_base.c ft_float_count.c ft_ftoa.c ft_strjoin_update.c \
				ft_swap.c ft_lstswap.c ft_min.c ft_max.c ft_atol.c \

PRINTF_SRC	=	char_printf.c flags_printf.c int_printf.c length_tools.c \
				pointers_printf.c ft_printf.c tools.c get_formats.c bonus.c

NODE_SRC	=	ft_nodeadd_end.c ft_nodeadd_front.c ft_nodedel_front.c ft_nodedel.c ft_nodenew.c ft_nodepop.c \
				ft_nodeswap.c ft_nodeprint.c

SRCS		=	$(LIBFT_SRC) $(PRINTF_SRC) $(NODE_SRC)

LIBFT_DIR = libft/
PRINTF_DIR = ft_printf/
NODE_DIR = node_struct/
OBJ_DIR		=	obj/
OBJS		=	$(patsubst %, $(OBJ_DIR)%, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@printf "Libft compiled!\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	
$(OBJ_DIR)%.o: $(LIBFT_DIR)%.c
	@gcc $(FLAGS) -o $@ -c $<
	
$(OBJ_DIR)%.o: $(PRINTF_DIR)%.c
	@gcc $(FLAGS) -o $@ -c $<
		
$(OBJ_DIR)%.o: $(NODE_DIR)%.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
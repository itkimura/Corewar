/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:46 by thle              #+#    #+#             */
/*   Updated: 2022/12/13 09:42:59 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define HASHTABLESIZE 16
# define ERROR 1
# define SUCCESS 0
# define MALLOCFAIL "Malloc fail"
# define OPSIZE 256

# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <string.h>
# include <stdbool.h>

typedef struct s_statement
{
	char		*name;
	int			code;
	bool		argcode;
	u_int16_t	args;
}	t_statement;

typedef struct s_hashstatement
{
	char					*name;
	int						index;
	struct s_hashstatement 	*next;
} t_hashstatement;

typedef struct s_labels
{
	char			*ptr;
	char			*name;
	struct s_labels	*next;
}	t_labels;

typedef struct s_op
{
	char	*instruction;
	char	*statement;
	char	*arg[3];
	int		totalbyte;
	int		byte;
}	t_op;

typedef struct s_asmdata
{
	t_op			**oplist;
	t_hashstatement	**hashtable;
	t_labels		**labels;
	header_t		*header;
	int				opsize;
	int				opcount;
	int				name;
	int				comment;
	bool			leaks;
}	t_asmdata;

static const t_statement	g_statements[HASHTABLESIZE] = {
{.code = 1, .name = "live", .argcode = false, .args = 0b010000000},
{.code = 2, .name = "ld", .argcode = true, .args = 0b011100000},
{.code = 3, .name = "st", .argcode = true, .args = 0b100101000},
{.code = 4, .name = "add", .argcode = true, .args = 0b100100100},
{.code = 5, .name = "sub", .argcode = true, .args = 0b100100100},
{.code = 6, .name = "and", .argcode = true, .args = 0b111111100},
{.code = 7, .name = "or", .argcode = true, .args = 0b111111100},
{.code = 8, .name = "xor", .argcode = true, .args = 0b111111100},
{.code = 9, .name = "zjmp", .argcode = false, .args = 0b010000000},
{.code = 10, .name = "ldi", .argcode = true, .args = 0b111110100},
{.code = 11, .name = "sti", .argcode = true, .args = 0b100111110},
{.code = 12, .name = "fork", .argcode = false, .args = 0b010000000},
{.code = 13, .name = "lld", .argcode = true, .args = 0b011100000},
{.code = 14, .name = "lldi", .argcode = true, .args = 0b111110100},
{.code = 15, .name = "lfork", .argcode = false, .args = 0b010000000},
{.code = 16, .name = "aff", .argcode = true, .args = 0b100000000},
};

void	free_exit(t_asmdata *data, char *str, bool is_error);
int		get_statement_index(t_asmdata *data, char *name);
int		init_statements_table(t_asmdata *data);
int		read_input(t_asmdata *data, char *argv);
int		init_op_table(t_op	***oplist, int size);
int		resize_op_table(t_asmdata *data);
int		init_op(t_op **op, char *line);
void	parse_instructions(t_asmdata *data);


/* 
**	Label functions
*/

int		init_labels_table(t_asmdata *data);
int		get_label_adr(t_asmdata *data, char **ptr, char *name);
void	insert_label(t_asmdata *data, char *name, char *ptr);

/* 
** Hash functions
*/

unsigned long	hash(char *str);

/*
** Debugger tools
*/

void	print_hashtable(t_asmdata *data);
void	print_statement(t_asmdata *data, char *name);
void	print_hashlabel(t_asmdata *data);
void	print_oplist(t_asmdata *data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:46 by thle              #+#    #+#             */
/*   Updated: 2023/02/27 14:30:30 by ccariou          ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_statement
{
	char		*name;
	bool		argcode;
	u_int16_t	args;
	int			arg_count;
	int			code;
	int			size;
}	t_statement;

typedef struct s_hashstatement
{
	char					*name;
	int						index;
	struct s_hashstatement	*next;
}	t_hashstatement;

typedef struct s_op
{
	char		*instruction;
	char		*label;
	char		*statement;
	char		*arg[3];
	u_int16_t	args;
	int			arg_count;
	int			argcode;
	int			totalbyte;
	int			byte;
}	t_op;

typedef struct s_labels
{
	t_op			*ptr;
	char			*name;
	struct s_labels	*next;
}	t_labels;

typedef struct s_asmdata
{
	t_op			**oplist;
	t_hashstatement	**hashtable;
	t_labels		**labels;
	t_header		*header;
	int				opsize;
	int				opcount;
	int				name;
	int				comment;
	bool			leaks;
}	t_asmdata;

/* 
	args binary 3 groups = 3 x 000;
	first =  T_IND 
	second = T_DIR %
	third = T_REG r
*/

static const t_statement	g_statements[HASHTABLESIZE] = {
{.code = 1, .name = "live", .argcode = false, .args = 0b010000000, .arg_count = 1, .size = 4},
{.code = 2, .name = "ld", .argcode = true, .args = 0b110001000, .arg_count = 2, .size = 4},
{.code = 3, .name = "st", .argcode = true, .args = 0b001101000, .arg_count = 2, .size = 4},
{.code = 4, .name = "add", .argcode = true, .args = 0b001001001, .arg_count = 3, .size = 4},
{.code = 5, .name = "sub", .argcode = true, .args = 0b001001001, .arg_count = 3, .size = 4},
{.code = 6, .name = "and", .argcode = true, .args = 0b111111001, .arg_count = 3, .size = 4},
{.code = 7, .name = "or", .argcode = true, .args = 0b111111001, .arg_count = 3, .size = 4},
{.code = 8, .name = "xor", .argcode = true, .args = 0b111111001, .arg_count = 3, .size = 4},
{.code = 9, .name = "zjmp", .argcode = false, .args = 0b010000000, .arg_count = 1, .size = 2},
{.code = 10, .name = "ldi", .argcode = true, .args = 0b111011001, .arg_count = 3, .size = 2},
{.code = 11, .name = "sti", .argcode = true, .args = 0b001111011, .arg_count = 3, .size = 2},
{.code = 12, .name = "fork", .argcode = false, .args = 0b010000000, .arg_count = 1, .size = 2},
{.code = 13, .name = "lld", .argcode = true, .args = 0b110001000, .arg_count = 2, .size = 4},
{.code = 14, .name = "lldi", .argcode = true, .args = 0b111011001, .arg_count = 3, .size = 2},
{.code = 15, .name = "lfork", .argcode = false, .args = 0b010000000, .arg_count = 1, .size = 2},
{.code = 16, .name = "aff", .argcode = true, .args = 0b001000000, .arg_count = 1, .size = 4},
};

int			read_input(t_asmdata *data, char *argv);
void		seperate_instruction(t_asmdata *data, char *ptr, int index, int i);
void		parse_instructions(t_asmdata *data);
void		check_instruction(t_asmdata *data, char *ptr, int index, int i);
int			check_size(char *str, int code);
int			check_if_label_exists(t_asmdata *data);
void		free_exit(t_asmdata *data, char *str, bool is_error);
void		add_byte_to_op(t_asmdata *data, int index, int arg_code, int tmp_index);
int			check_comment_after_arg(char *arg);

/* 
**	Op functions
*/

int			init_op_table(t_op ***oplist, int size);
int			resize_op_table(t_asmdata *data);
int			init_op(t_op **op, char *line);

/* 
**	Statement functions
*/

int			validate_statement(t_asmdata *data, char *ptr, int index, int *i);
int			init_statements_table(t_asmdata *data);
int			get_statement_index(t_asmdata *data, char *name);

/* 
**	Label functions
*/

int			validate_label(t_asmdata *data, char *ptr, int index);
int			init_labels_table(t_asmdata *data);
int			get_label_adr(t_asmdata *data, t_op **ptr, char *name);
// void		insert_label(t_asmdata *data, t_op *ptr, char *name);

/*
** Writing functions 
*/

void		write_to_file(t_asmdata *data, char *filename);
void		write_name(t_asmdata *data, int fd);
void		write_comment(t_asmdata *data, int fd);
void		write_size(t_asmdata *data, int fd);
char		*change_filename(char *filename);
void		convert_arg(t_op **tmp, int fd, int j);
int			ft_atoi_base(const char *str, int base);
int			byte_shift_translate(int value);

/* 
** Hash functions
*/

uint32_t	hash(char *str);

/*
** Bonus: Debugger tools
*/

void		print_hashtable(t_asmdata *data);
void		print_statement(t_asmdata *data, char *name);
void		print_hashlabel(t_asmdata *data);
void		print_oplist(t_asmdata *data);

#endif

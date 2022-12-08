/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:46 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 14:23:25 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# define HASHTABLESIZE 16

# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <string.h>
# include <stdbool.h>

typedef struct s_statement
{
	char			*name;
	int				code;
	bool			argcode;
	u_int16_t	args;
}	t_statement;

typedef struct s_hashstatement
{
	char										*name;
	int											index;
	struct s_hashstatement 	*next;
} t_hashstatement;

typedef struct s_labels
{
	char						*label;
	int							index;
	struct s_labels	*next;
}	t_labels;

typedef struct s_asmdata
{
	t_hashstatement	**hashtable;
	t_labels				**labels;
	char						**instructions;
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

void	free_exit(t_asmdata *data);
int		get_index(t_asmdata *data, char *name);

/* 
**	Label functions
*/

int		init_labels(t_asmdata *data);
void	insert_label(t_asmdata *data, char *label);
void	get_label_index(t_asmdata *data, char *label);

/* 
** Hash functions
*/

int		init_hashtable(t_asmdata *data);

/*
** tempfunctions to be removed
*/

void	print_hashtable(t_asmdata *data);
void	print_statement(t_asmdata *data, char *name);

#endif
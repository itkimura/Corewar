/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:46 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 11:54:02 by leo              ###   ########.fr       */
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

typedef struct s_statements
{
	char			*name;
	int				code;
	bool			argcode;
	u_int16_t	args;
}	t_statements;

typedef struct s_hashstatement
{
	char					*name;
	int						index;
	struct s_hashstatement 	*next;
} t_hashstatement;

typedef struct s_asmdata
{
	t_hashstatement	**hashtable;	
}	t_asmdata;

static const t_statements	g_statements[16] = {
{.code = 1, .name = "live", .argcode = false, .args = 0},
{.code = 2, .name = "ld", .argcode = true, .args = 0},
{.code = 3, .name = "st", .argcode = true, .args = 0},
{.code = 4, .name = "add", .argcode = true, .args = 0},
{.code = 5, .name = "sub", .argcode = true, .args = 0},
{.code = 6, .name = "and", .argcode = true, .args = 0},
{.code = 7, .name = "or", .argcode = true, .args = 0},
{.code = 8, .name = "xor", .argcode = true, .args = 0},
{.code = 9, .name = "zjmp", .argcode = false, .args = 0},
{.code = 10, .name = "ldi", .argcode = true, .args = 0},
{.code = 11, .name = "sti", .argcode = true, .args = 0},
{.code = 12, .name = "fork", .argcode = false, .args = 0},
{.code = 13, .name = "lld", .argcode = true, .args = 0},
{.code = 14, .name = "lldi", .argcode = true, .args = 0},
{.code = 15, .name = "lfork", .argcode = false, .args = 0},
{.code = 16, .name = "aff", .argcode = true, .args = 0},
};

void	free_exit(t_asmdata *data);
int		init_hashtable(t_asmdata *data);
int		get_statement_index(char *name);

/* tempfunctions */

void	print_hashtable(t_asmdata *data);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:46 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 09:44:21 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <string.h>
# include <stdbool.h>

typedef struct s_statements
{
	char			*name;
	int				index;
	bool			argcode;
	u_int16_t	args;
}	t_statements;

static const t_statements	g_statements[16] = {
{.name = "live", .index = 0, .argcode = false, .args = 0},
{.name = "ld", .index = 1, .argcode = true, .args = 0},
{.name = "st", .index = 2, .argcode = true, .args = 0},
{.name = "add", .index = 3, .argcode = true, .args = 0},
{.name = "sub", .index = 4, .argcode = true, .args = 0},
{.name = "and", .index = 5, .argcode = true, .args = 0},
{.name = "or", .index = 6, .argcode = true, .args = 0},
{.name = "xor", .index = 7, .argcode = true, .args = 0},
{.name = "zjmp", .index = 8, .argcode = false, .args = 0},
{.name = "ldi", .index = 9, .argcode = true, .args = 0},
{.name = "sti", .index = 10, .argcode = true, .args = 0},
{.name = "fork", .index = 11, .argcode = false, .args = 0},
{.name = "lld", .index = 12, .argcode = true, .args = 0},
{.name = "lldi", .index = 13, .argcode = true, .args = 0},
{.name = "lfork", .index = 14, .argcode = false, .args = 0},
{.name = "aff", .index = 15, .argcode = true, .args = 0},
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:31:30 by thle              #+#    #+#             */
/*   Updated: 2023/01/19 15:59:53 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: zjmp
 *
 * Info:
 * code:			9 (9)
 * arg_type_code:	false
 * number of args:	1
 * arguments:		{T_DIR}
 *
 * Tasks:
 * This op is only performed when carry is true
 * The pc is set to perform the next pc which will be located at:
 * current position + <FIRST_ARGUMENT> % IDX_MOD
 *
 */
bool	op_zjmp(t_game *game, t_carriage *carriage)
{
	int	pos;

	if (carriage->carry == true)
	{
		pos = carriage->pc
			+ get_value(game, carriage, FIRST_ARG, true) % IDX_MOD;
		if (pos < 0)
			pos = MEM_SIZE + pos;
		carriage->next_statement_pc = pos % MEM_SIZE;
	}
	return (true);
}

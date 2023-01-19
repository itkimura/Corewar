/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:32:17 by thle              #+#    #+#             */
/*   Updated: 2023/01/19 15:55:21 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: st
 *
 * Info:
 * code:			3 (3)
 * arg_type_code:	true
 * number of args:	2
 * arguments:		{T_REG, T_IND | T_REG}
 *
 * Tasks:
 * Value = value of T_REG that is passed as FIRST_ARG
 * If SECOND_ARG is T_REG, write value to this reg
 * If SECOND_ARG is T_IND, get the position from arg (truncated by IDX_MOD
 * needed) then place value onto the arena starting from this position.
 * 
 */
bool	op_st(t_game *game, t_carriage *carriage)
{
	int	value;
	int	pos;
	int	reg_index;

	value = get_value(game, carriage, FIRST_ARG, true);
	if (carriage->arg[SECOND_ARG] == T_REG)
	{
		reg_index = carriage->arg_value[SECOND_ARG] - 1;
		carriage->registry[reg_index] = value;
	}
	else
	{
		pos = carriage->pc + (carriage->arg_value[SECOND_ARG] % IDX_MOD);
		if (pos < 0)
			pos = MEM_SIZE + pos;
		place_value(game, value, pos % MEM_SIZE);
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:13 by thle              #+#    #+#             */
/*   Updated: 2023/01/25 15:27:41 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: lldi
 *
 * Info:
 * code:			14 (0e)
 * arg_type_code:	true
 * number of args:	3
 * arguments:		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
 *
 * Tasks:
 * pos = current position + (result of SECOND_ARG + result of THIRD_ARG)
 * Value = read 4 bytes starting from pos
 * Write value into the reg that is passed as THIRD_ARG
 *
 */
bool	op_lldi(t_game *game, t_carriage *carriage)
{
	int	reg_index;
	int	pos;

	reg_index = carriage->arg_value[THIRD_ARG] - 1;
	carriage->arg_value[FIRST_ARG]
		= get_value(game, carriage, FIRST_ARG, true);
	carriage->arg_value[SECOND_ARG]
		= get_value(game, carriage, SECOND_ARG, true);
	pos = (carriage->pc
			+ (carriage->arg_value[FIRST_ARG]
				+ carriage->arg_value[SECOND_ARG])) % MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	carriage->registry[reg_index]
		= char_to_int(game->arena, pos % MEM_SIZE, 4, true);
	return (true);
}

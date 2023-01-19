/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:35:09 by thle              #+#    #+#             */
/*   Updated: 2023/01/19 15:48:09 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: ldi
 *
 * Info:
 * code:			10 (0a)
 * arg_type_code:	true
 * number of args:	3
 * arguments:		{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}
 *
 * Tasks:
 * pos = current position + (result of SECOND_ARG + result of THIRD_ARG)
 * 																	% IDX_MOD
 * Value = read 4 bytes starting from pos
 * Write value into the reg that is passed as THIRD_ARG
 *
 */
bool	op_ldi(t_game *game, t_carriage *carriage)
{
	int	reg_index;
	int	pos;

	reg_index = carriage->arg_value[THIRD_ARG] - 1;
	pos = (carriage->pc
			+ (get_value(game, carriage, FIRST_ARG, true)
				+ get_value(game, carriage, SECOND_ARG, true)) % IDX_MOD)
		% MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	carriage->registry[reg_index] = char_to_int(game->arena,
			pos % MEM_SIZE, 4, true);
	return (true);
}

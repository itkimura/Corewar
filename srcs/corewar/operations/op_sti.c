/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:35:30 by thle              #+#    #+#             */
/*   Updated: 2023/01/14 03:23:18 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: sti
 *
 * Info:
 * code:			11 (0b)
 * arg_type_code:	true
 * number of args:	3
 * arguments:		{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}
 *
 * Tasks:
 * Value = value of T_REG that is passed as FIRST_ARG
 * pos = (result of SECOND_ARG + result of THIRD_ARG) % IDX_MOD
 * Place the value onto the arena starting from collected postition.
 *
 */
bool	op_sti(t_game *game, t_carriage *carriage)
{
	int value;
	int pos;
	
	value = get_value(game, carriage, FIRST_ARG, true);
	pos = (carriage->pc +
			((get_value(game, carriage, SECOND_ARG, true) +
			get_value(game, carriage, THIRD_ARG, true)) % IDX_MOD)) % MEM_SIZE;
	if (pos < 0)
		pos = MEM_SIZE + pos;
	place_value(game, value, pos % MEM_SIZE);
	return (true);
}

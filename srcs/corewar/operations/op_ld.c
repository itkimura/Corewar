/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:31:59 by thle              #+#    #+#             */
/*   Updated: 2023/01/14 02:25:31 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: ld
 *
 * Info:
 * code:			2 (2)
 * arg_type_code:	true
 * number of args:	2
 * arguments:		{T_DIR | T_IND, T_REG}
 *
 * Tasks:
 * Get the value of from FIRST_ARG, if FIRST_ARG is T_IND, then it should be
 * truncated with IDX_MOD
 * Then write the value to registry that is passed from SECOND_ARG.
 * If value is 0, carry is set to 1. Else, carry is set to 0.
 *
 */
bool op_ld(t_game *game, t_carriage *carriage)
{
	int	value;
	int reg_index;

	reg_index = carriage->arg_value[SECOND_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, true);
	carriage->registry[reg_index] = value;
	carriage->carry = (value == 0);
	return true;
}

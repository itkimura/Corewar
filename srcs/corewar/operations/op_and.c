/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:33:58 by thle              #+#    #+#             */
/*   Updated: 2023/01/14 02:18:07 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: and
 * 
 * Info:
 * code:			6 (6)
 * arg_type_code:	true
 * number of args:	3
 * arguments:		{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}
 *
 * Tasks:
 * value = result of FIRST_ARG & result of SECOND_ARG
 * then value will be written to the reg that corresponding the THIRD_ARG
 * If value is 0, carry is set to 1. Else, carry is set to 0.
 *
 */
bool	op_and(t_game *game, t_carriage *carriage)
{
	int reg;
	int value;

	reg = carriage->arg_value[THIRD_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, true) &
			get_value(game, carriage, SECOND_ARG, true);
	carriage->registry[reg] = value;
	carriage->carry = (value == 0);
	return true;
}

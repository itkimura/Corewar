/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:34:23 by thle              #+#    #+#             */
/*   Updated: 2023/01/25 15:28:01 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: or
 * 
 * Info:
 * code:			7 (7)
 * arg_type_code:	true
 * number of args:	3
 * arguments:		{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}
 *
 * Tasks:
 * value = result of FIRST_ARG | result of SECOND_ARG
 * then value will be written to the reg that corresponding the THIRD_ARG
 * If value is 0, carry is set to 1. Else, carry is set to 0.
 *
 */
bool	op_or(t_game *game, t_carriage *carriage)
{
	int	reg;
	int	value;

	reg = carriage->arg_value[THIRD_ARG] - 1;
	carriage->arg_value[FIRST_ARG]
		= get_value(game, carriage, FIRST_ARG, true);
	carriage->arg_value[SECOND_ARG]
		= get_value(game, carriage, SECOND_ARG, true);
	value = carriage->arg_value[FIRST_ARG] | carriage->arg_value[SECOND_ARG];
	carriage->registry[reg] = value;
	carriage->carry = (value == 0);
	return (true);
}

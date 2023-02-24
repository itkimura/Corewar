/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:33:00 by thle              #+#    #+#             */
/*   Updated: 2023/02/24 10:59:06 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: add
 * 
 * Info:
 * code:			4 (4)
 * arg_type_code:	true
 * number of args:	3
 * arguments:		{T_REG, T_REG, T_REG}
 *
 * Tasks:
 * value = result of FIRST_ARG + result of SECOND_ARG
 * then value will be written to the reg that corresponding the THIRD_ARG
 * If value is 0, carry is set to 1. Else, carry is set to 0.
 *
 */
bool	op_add(t_game *game, t_carriage *carriage)
{
	int	value;
	int	reg_index;

	reg_index = carriage->arg_value[THIRD_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, true)
		+ get_value(game, carriage, SECOND_ARG, true);
	carriage->registry[reg_index] = value;
	carriage->carry = (value == 0);
	return (true);
}

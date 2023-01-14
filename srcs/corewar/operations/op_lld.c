/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:35:51 by thle              #+#    #+#             */
/*   Updated: 2023/01/14 02:04:40 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: lld
 *
 * Info:
 * code:			13 (0d)
 * arg_type_code:	true
 * number of args:	2
 * arguments:		{T_DIR | T_IND, T_REG}
 *
 * Tasks:
 * Get the value of from FIRST_ARG.
 * Then write the value to registry that is passed from SECOND_ARG.
 * If value is 0, carry is set to 1. Else, carry is set to 0.
 *
 */
bool	op_lld(t_game *game, t_carriage *carriage)
{

	int	value;
	int reg_index;

	reg_index = carriage->arg_value[SECOND_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, false);
	carriage->registry[reg_index] = value;
	carriage->carry = (value == 0);
	return (true);
}

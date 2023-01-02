/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:34:23 by thle              #+#    #+#             */
/*   Updated: 2023/01/02 15:29:30 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
*or* performs a "bitwise AND" statement for the values ​of
the first two arguments and writes the result to the registry passed as
the third argument.

If the recorded result was equal to zero,
then the value of carry must be set equal to 1.
If the result was not zero, then - equal to 0.

Since the first and second arguments can be one of three types,
we will consider how to get the value of each of them:

Argument #1 / Argument #2 - T_REG
In this case, the value is taken from the registry passed as an argument.

Argument #1 / Argument #2 - T_DIR
In this case, the numerical value passed as an argument is used.

Argument #1 / Argument #2 - T_IND
If the argument type is T_IND,
then it is necessary to set the address from which 4 bytes will be read.

The address is defined as follows - current position + <ARGUMENT> % IDX_MOD.

The 4-byte number read at this address will be the required value.
*/

bool	op_or(t_game *game, t_carriage *carriage)
{
	int reg;
	int value;

	reg = carriage->arg_value[THIRD_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, true) |
			get_value(game, carriage, SECOND_ARG, true);
	carriage->registry[reg] = value;
	carriage->carry = (value == 0);
	return true;
}

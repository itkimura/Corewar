/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:32:17 by thle              #+#    #+#             */
/*   Updated: 2023/01/09 14:00:06 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*

This statement writes a value from the registry that was passed
as the first parameter. However, the location of writing depends on
the type of the second argument:


Argument #2 - T_REG ------------------------------------------------------------
If the second argument matches the type T_REG,
then the value is written to the registry.

For example, in this case,
the value from registry number 7 is written to registry with number 11:
st    r7, r11

Argument #2 - T_IND ------------------------------------------------------------
As we recall arguments like T_IND this is about relative addresses.
Therefore, in this case, the statement procedure of the statement st is as follows:

Truncate the value of the second argument by the modulo IDX_MOD.

Define the address: current position + <SECOND_ARGUMENT> % IDX_MOD

Write the value from the registry, which was transferred as the first argument,
into memory at the received address.

*/


bool	op_st(t_game *game, t_carriage *carriage)
{
	int value;
	int pos;
	int reg;

	value = get_value(game, carriage, FIRST_ARG, true);
	// value = 300;
	if (carriage->arg[SECOND_ARG] == T_REG)
	{
		reg = carriage->arg_value[SECOND_ARG] - 1;
		carriage->registry[reg] = value;
	}
	else
	{
		// ft_printf("else statement op_st\n");
		pos = (carriage->pc + (carriage->arg_value[SECOND_ARG] % IDX_MOD)) % MEM_SIZE;
		place_value(game, value, pos);
	}
	// uint32_t nbr = (uint32_t)value;
	// ft_printf("nbr is %u\n", nbr);
	return true;
}

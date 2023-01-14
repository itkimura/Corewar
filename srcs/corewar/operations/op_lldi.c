/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:13 by thle              #+#    #+#             */
/*   Updated: 2023/01/13 16:49:14 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
At its core, this statement is similar to the ldi statement.

It writes the value to the registry,which was passed to it as the third parameter.
The value that this statement writes is 4 bytes that it read.

The bytes are read at the address, which is formed according to the following
principle: current position + (<FIRST_ARGUMENT_VALUE> + <SECOND_ARGUMENT_VALUE>).

Unlike the ldi statement, in this case, when forming the address,
you shouldn't truncate by modulo IDX_MOD.

For arguments like T_IND everything remains as before

If we get an argument of type T_IND as the first or as second argument,
then we still read 4 bytes of the value at the address:
current position + <ARGUMENT> % IDX_MOD.
Truncation by modulo is preserved.
*/

bool	op_lldi(t_game *game, t_carriage *carriage)
{
	int reg_index;
	unsigned int pos;

	reg_index = get_value(game, carriage, THIRD_ARG, true) - 1;
	pos = (carriage->pc +
		get_value(game, carriage, FIRST_ARG, true) +
		get_value(game, carriage, SECOND_ARG, true)) % MEM_SIZE;
	carriage->registry[reg_index] = char_to_int(game->arena, pos, 4, true);
	return true;
}

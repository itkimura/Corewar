/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:35:09 by thle              #+#    #+#             */
/*   Updated: 2023/01/13 16:46:51 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
This statement writes the value to the registry, which was passed to it as
the third parameter. The value it writes is 4 bytes. It reads these 4 bytes at
the address, which is formed according to the following principle:
current position + (<FIRST_ARGUMENT_VALUE> + <SECOND_ARGUMENT_VALUE>) % IDX_MOD.
*/

#include "corewar.h"

bool op_ldi(t_game *game, t_carriage *carriage)
{
	// print_single_carriage(carriage);
	int reg_index;
	unsigned int pos;

	reg_index = carriage->arg_value[THIRD_ARG] - 1;
	pos = (carriage->pc +
		(get_value(game, carriage, FIRST_ARG, true) +
		get_value(game, carriage, SECOND_ARG, true)) % IDX_MOD) % MEM_SIZE;
	carriage->registry[reg_index] = char_to_int(game->arena, pos, 4, true);
	return true;
}

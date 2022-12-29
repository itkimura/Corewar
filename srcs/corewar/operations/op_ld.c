/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:31:59 by thle              #+#    #+#             */
/*   Updated: 2022/12/29 22:39:23 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
The task of this statement is to load the value into the registry.
But its behavior differs depending on the type of the first argument:

Argument #1 - T_DIR ------------------------------------------------------------

If the type of the first argument is T_DIR,
then the number passed as an argument will be taken "as is".

Objectives of the statement:

Write the number in the registry, which was passed as the second argument.

If the number 0 is written in the registry, then set the value of *carry* to 1.
If a non-zero value was written, set carry to 0.

Argument #1 - T_IND ------------------------------------------------------------

If the type of the first argument is T_IND,
then the number represents the address.

If an argument of this type is received,
it is truncated by modulo - <FIRST_ARGUMENT> % IDX_MOD.

Define the address - current position + <FIRST_ARGUMENT> % IDX_MOD.

4 bytes must be read from the received address.

Write the read number to the registry that was passed as the second parameter.

If 0 is written into the registry, then set the value of *carry* to 1.
If a non-zero value was written, then set carry to 0.
*/

bool op_ld(t_game *game, t_carriage *carriage)
{
	ft_printf("\n");
	print_arg_and_val(carriage);
	
	int	value;
	int reg;

	reg = carriage->arg_value[SECOND_ARG] - 1;
	if (carriage->arg[FIRST_ARG] == T_DIR)
	{
		value = carriage->arg_value[FIRST_ARG];
	}
	else
	{
		value = reverse_bytes(game->arena,
				(carriage->pc + carriage->arg_value[FIRST_ARG] % IDX_MOD) % MEM_SIZE,
				4);
	}
	carriage->registry[reg] = value;
	carriage->carry = (value == 0);
	ft_printf("r%d - %d\n", reg + 1, value);
	ft_printf("carry: %d\n", carriage->carry);
	return true;
}

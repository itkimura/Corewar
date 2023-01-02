/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:33:00 by thle              #+#    #+#             */
/*   Updated: 2023/01/02 13:42:35 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*

The task of the add:

Sum the value from the registry that was passed as the first argument,
with the value of the registry that was passed as the second argument.

Write the result to the registry, which was passed as the third argument.

If the received sum, which we recorded in the third argument,
was equal to zero, then set carry to 1. And if the sum was not zero - in 0.

*/

bool	op_add(t_game *game, t_carriage *carriage)
{
	ft_printf("\n");
	print_arg_and_val(carriage);

	int value;
	int reg;

	(void) game;
	reg = carriage->arg_value[THIRD_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, true) +
			get_value(game, carriage, SECOND_ARG, true);
	carriage->registry[reg] = value;
	carriage->carry = (value == 0);

	// ft_printf("first: %d\n", get_value(game, carriage, FIRST_ARG, true));
	// ft_printf("second: %d\n", get_value(game, carriage, SECOND_ARG, true));

	// ft_printf("r%d - %d\n", reg + 1, value);
	// ft_printf("carry: %d\n", carriage->carry);
	return true;
}



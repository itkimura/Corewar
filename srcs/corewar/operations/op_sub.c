/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:33:35 by thle              #+#    #+#             */
/*   Updated: 2022/12/30 13:44:00 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*

Its tasks:

From the value of the registry passed as the first argument,
subtract the value of the registry that was passed as the second argument.

The result is written in the registry, which was passed as the third argument.

If the recorded result was equal to zero,
then make the value of carry equal to 1.
If the result was not zero, then set it to 0.

*/

bool	op_sub(t_game *game, t_carriage *carriage)
{
	// ft_printf("\n");
	// print_arg_and_val(carriage);
	// (void) carriage;

	int value;
	int reg;

	(void) game;
	reg = carriage->arg_value[THIRD_ARG] - 1;
	value = get_value(game, carriage, FIRST_ARG, true) -
			get_value(game, carriage, SECOND_ARG, true);
	carriage->registry[reg] = value;
	carriage->carry = (value == 0);

	// ft_printf("r%d - %d\n", reg + 1, value);
	// ft_printf("carry: %d\n", carriage->carry);
	return true;
}
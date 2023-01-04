/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:42 by thle              #+#    #+#             */
/*   Updated: 2023/01/04 16:42:22 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * "aff" means  takes a value from a registry that was passed as a single
 * argument. Converts it to type char. And displays as an ASCII character.
 */
bool op_aff(t_game *game, t_carriage *carriage)
{
	if (get_arg_value(carriage, game->arena))
	{
		if (game->flags_value[FLAG_A])
			ft_printf("%c\n", (char)carriage->registry[carriage->arg_value[0] - 1]);
		if (game->flags_value[FLAG_V] == 16)
			print_v(game, carriage, 3);
	}
	carriage->remaining_cycle = g_op_tab[OP_AFF].cycles;
	return (true);
}

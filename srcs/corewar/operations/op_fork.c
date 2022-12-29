/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:38:53 by thle              #+#    #+#             */
/*   Updated: 2022/12/28 15:46:40 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * fork:makes a copy of the carriage.
 * And this copy is placed at the address <FIRST_ARGUMENT> % IDX_MOD.
 *
 * What data is being copied?
 * [1]:Values of all registrys
 * [2]:The value of carry
 * [3]:The number of the cycle in which the last statement live performed
 * [4]:And something else, but more on that later.
 *
 * % MEM_SIZE -> if it is 4096 + 3, then 4099 %(4*1024) = 4099 % 4096 = 3.
 */
bool op_fork(t_game *game, t_carriage *carriage)
{
	int shift;

	shift = reverse_bytes(game->arena, carriage->pc + 1,  g_op_tab[11].t_dir_size);

	// shift = reverse_bytes(game, carriage->pc + 1, 2);
	if (add_carriage(game, carriage,
					 (unsigned int)(carriage->pc + (shift % IDX_MOD)) % MEM_SIZE) == false)
		return (false);
	carriage->pc += 3; // move position 3 bytes ahead
	carriage->pc %= MEM_SIZE;
	return (true);
}
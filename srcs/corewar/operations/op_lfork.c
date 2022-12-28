/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:39:05 by thle              #+#    #+#             */
/*   Updated: 2022/12/28 15:48:02 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * this statement is similar to the fork statement.
 * Except for the fact that a new carriage is created at the address
 * : current position + <FIRST_ARGUMENT>
 * In the lfork statement, truncation by modulo is not necessary.
 */
bool op_lfork(t_game *game, t_carriage *carriage)
{
	int shift;

	shift = reverse_bytes(game->arena, carriage->pc + 1, g_op_tab[11].t_dir_size);
		ft_printf("shift:%d\n", shift);
	// shift = reverse_bytes(game, carriage->pc, + 1, 2);
	if (add_carriage(game, carriage,
					 (unsigned int)(carriage->pc + shift) % MEM_SIZE) == false)
		return (false);
	carriage->pc += 3;
	carriage->pc %= MEM_SIZE;
	return (true);
}
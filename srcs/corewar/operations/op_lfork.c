/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:39:05 by thle              #+#    #+#             */
/*   Updated: 2023/01/12 15:50:57 by thule            ###   ########.fr       */
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

	shift = char_to_int(game->arena, carriage->pc + 1, g_op_tab[OP_LFORK].t_dir_size);
	// ft_printf("shift:%d\n", shift);
	// shift = char_to_int(game, carriage->pc, + 1, 2);
	if (add_carriage(game, carriage,
					 (unsigned int)(carriage->pc + shift) % MEM_SIZE) == false)
		return (false);
	// update_next_statement_pc(carriage);
	return (true);
}
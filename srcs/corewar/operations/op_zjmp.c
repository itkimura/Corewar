/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:31:30 by thle              #+#    #+#             */
/*   Updated: 2023/01/10 13:39:49 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * This statement is affected by the value of the carry flag.
 *
 * If it is equal to 1,then the function updates the value of PC
 * to the address: current position + <FIRST_ARGUMENT> % IDX_MOD.
 *
 * That is, zjmp sets where the carriage should move to perform the next statement.
 * This allows us to jump in memory to the desired position,
 * and not to do everything in order.
 *
 * If the carry value is zero, no movement is performed.
 */

bool op_zjmp(t_game *game, t_carriage *carriage)
{
	if (carriage->carry == true)
	{
		carriage->next_statement_pc = (carriage->pc +
						char_to_int(game->arena, carriage->pc + 1, 2) % IDX_MOD) %
					   MEM_SIZE;
	}
	return true;
}

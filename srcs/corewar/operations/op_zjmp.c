/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:31:30 by thle              #+#    #+#             */
/*   Updated: 2023/01/02 17:25:03 by itkimura         ###   ########.fr       */
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
bool	op_zjmp(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	/*
	int shift;

	shift = reverse_bytes(game->arena, carriage->pc + 1,  g_op_tab[11].t_dir_size);
	if (get_arg_value(carriage, game->arena))
	{
		if (carriage->carry == 1)
			carriage->pc = reverse_
	}
	carriage->pc += ;
	carriage->pc %= MEM_SIZE;
	*/
	return false;
}

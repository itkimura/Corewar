/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:30:10 by thle              #+#    #+#             */
/*   Updated: 2023/01/03 15:34:37 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * The live statement has two functions:
 * 
 * It counts that carriage, which performs the live statement, is alive.
 * 
 * If the number specified as an argument to the statement live matches
 * the number of the player, then it will consider that the player is alive.
 * For example, if the argument value is -2,
 * then the player with the number 2 is alive.
*/
bool	op_live(t_game *game, t_carriage *carriage)
{
	int	player;

	carriage->live_performed = true;
	player = -(reverse_bytes(game->arena, carriage->pc + 1, 4));
	if (player > 0 && player <= game->total_players)
		game->winner = player;
	carriage->crossed_bytes = 4;
	carriage->remaining_cycle = g_op_tab[OP_LIVE].cycles;
	return true;
}

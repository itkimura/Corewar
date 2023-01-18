/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:30:10 by thle              #+#    #+#             */
/*   Updated: 2023/01/18 13:21:05 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: live
 *
 * Info:
 * code:			1 (1)
 * arg_type_code:	false
 * number of args:	1
 * arguments:		{T_DIR}
 *
 * Tasks:
 * Mark the live op has been performed by this carriage in this cycle_to_dies.
 * Mark in which number_of_cycles that it's just performed.
 * If its ((value of FIRST_ARG) * -1) belong to any player. Mark that value
 * of FIRST_ARG as winner.
 *
 */
bool	op_live(t_game *game, t_carriage *carriage)
{
	int	player;

	carriage->last_live_performed = game->number_of_cycles;
	carriage->live_performed = true;
	(game->number_of_live_statement)++;
	player = -(char_to_int(game->arena, carriage->pc + 1, 4, true));
	if (player > 0 && player <= game->total_players)
		game->winner = -player;
	if (game->flags_value[FLAG_L] == FO_LIVES)
		ft_printf("Player %d (%s) is said to be alive\n", player,
			game->players_in_order[player - 1]->name);
	return (true);
}

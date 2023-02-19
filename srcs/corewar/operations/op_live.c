/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:30:10 by thle              #+#    #+#             */
/*   Updated: 2023/01/25 13:25:06 by itkimura         ###   ########.fr       */
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
 * Mark in which total_cycles that it's just performed.
 * If its ((value of FIRST_ARG) * -1) belong to any player. Mark that value
 * of FIRST_ARG as winner.
 *
 */
bool	op_live(t_game *game, t_carriage *carriage)
{
	int	player;

	carriage->last_live_performed = game->total_cycles;
	(game->total_lives)++;
	player = -(carriage->arg_value[FIRST_ARG]);
	if (player > 0 && player <= game->total_players)
		game->winner = player;
	return (true);
}

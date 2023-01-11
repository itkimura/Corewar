/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:30:10 by thle              #+#    #+#             */
/*   Updated: 2023/01/11 12:41:06 by itkimura         ###   ########.fr       */
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

	ft_printf("---------- live ---------\n");
	carriage->live_performed = game->number_of_cycles;
	ft_printf("live_performed = %d\n", carriage->live_performed);
	player = -(char_to_int(game->arena, carriage->pc + 1, 4));
	if (player > 0 && player <= game->total_players)
		game->winner = player;
	if (game->flags_value[FLAG_L] == FO_LIVES)
		ft_printf("Player %d (%s) is said to be alive\n", player,
			game->players_in_order[player - 1]->name);
	return (true);
}

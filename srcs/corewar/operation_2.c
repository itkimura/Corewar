/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:28:41 by thule             #+#    #+#             */
/*   Updated: 2022/12/27 16:35:59 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
Take argument value from g_op_tab:

	0 1 0 0
or
	0 0 0 1
	
=	0 1 0 1
&	
	0 0 0 1
=	0 0 0 1 (== original value => correct)

	0 0 0 1
and
	0 0 1 0
=	0 0 0 0 (!= original value => wrong)
*/


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
	uint32_t	player;

	carriage->last_live_performed = game->number_of_cycles;
	player = bytes_to_decimal(game->arena, carriage->pc + 1, carriage->pc + 4);
	if (player > 0 && player <= game->total_players)
		game->winner = player;
	return true;
}

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
	return false;
}



bool	op_fork(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_lfork(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_ld(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_st(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_add(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_sub(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_and(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_or(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_xor(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_ldi(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_sti(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_lld(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_lldi(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}

bool	op_aff(t_game *game, t_carriage *carriage)
{
	(void) game;
	(void) carriage;
	return false;
}
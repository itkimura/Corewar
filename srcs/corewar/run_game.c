/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:18:49 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/24 13:29:40 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


void run_check(t_game *game)
{
	t_carriage *carriage;
	t_carriage *next;
	t_carriage *prev;

	carriage = game->carriage_head;
	prev = NULL;
	next = NULL;
	while (carriage)
	{
		next = carriage->next;
		if (carriage->live_performed == false)
		{
			if (game->flags_value[FLAG_L] == FO_DEATHS)
			{
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						  carriage->id, game->total_cycles - carriage->last_live_performed - 1,
						  game->cycles_to_die);
			}
			kill_carriage(game, prev, carriage, next);
		}
		else
		{
			carriage->live_performed = false;
			prev = carriage;
		}
		carriage = next;
	}
	if (game->total_lives >= NBR_LIVE || (game->total_checks % MAX_CHECKS == 0 && game->total_checks != 0))
	{
		game->cycles_to_die = game->cycles_to_die - CYCLE_DELTA;
		game->total_checks = 0;
	}
	game->check_counter = game->cycles_to_die;
	game->total_lives = 0;
	game->total_checks++;
}

bool run_carriages(t_game *game)
{
	t_carriage *carriage;

	carriage = game->carriage_head;
	while (carriage)
	{
		carriage->remaining_cycle--;
		if (carriage->remaining_cycle <= 0)
		{
			carriage->statement_index = game->arena[carriage->pc] - 1;
			if (is_op_code(carriage->statement_index) == true)
				carriage->remaining_cycle = g_op_tab[carriage->statement_index].cycles;
			else
			{
				carriage->pc = (carriage->pc + 1) % MEM_SIZE;
				carriage->remaining_cycle = 1;
			}
		}
		else if (carriage->remaining_cycle == 1)
		{
			if (get_arg_value(carriage, game->arena) == true)
			{
				if (g_op_tab[carriage->statement_index].f(game, carriage) == false)
					return (false);
			}
			flag_l(game, carriage);
			carriage->pc = carriage->next_statement_pc;
		}
		carriage = carriage->next;
	}
	return true;
}


bool run_game(t_game *game)
{
	int index;

	index = 0;
	while (game->carriage_head != NULL)
	{
		if (game->flags_value[FLAG_L] == FO_CYCLES)
			ft_printf("It is now cycle %d\n", game->total_cycles + 1);
		if (print_dump(game) == false)
			break;
		if (game->flags_value[FLAG_DUMP] == game->total_cycles)
		{
			print_arena(game);
			return (true);
		}
		run_carriages(game);
		game->total_cycles++;
		game->check_counter--;

		if (game->cycles_to_die <= 0 || game->check_counter <= 0)
			run_check(game);
		index++;
	}
	if (game->carriage_head == NULL)
		ft_printf("Contestant %d, \"%s\", has won !\n", (game->winner) * -1, game->players_in_order[(game->winner) * -1 - 1]->name);
	return (true);
}

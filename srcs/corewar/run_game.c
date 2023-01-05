/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:18:49 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/05 17:05:20 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void kill_carriage(t_game *game, t_carriage *prev, t_carriage *curr, t_carriage *next)
{
	if (game->carriage_head == curr)
		game->carriage_head = next;
	if (curr != NULL)
		free(curr);
	curr = NULL;
	if (prev != NULL)
		prev->next = next;
}

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
		// number_of_live_statement >= NBR_LIVE -> game->cycle_to_die - CYCLE_DELTA
		game->number_of_live_statement = 0;
		if (carriage->live_performed == false)
		{
			kill_carriage(game, prev, carriage, next);
		}
		else
		{
			carriage->live_performed = false;
			prev = carriage;
		}
		carriage = next;
	}
	if (game->number_of_live_statement >= NBR_LIVE || game->number_of_check % MAX_CHECKS == 0)
	{
		game->cycles_to_die = game->cycles_to_die - CYCLE_DELTA;
		game->number_of_check = 0;
	}
	game->number_of_live_statement = 0;
	game->number_of_check++;
}

bool run_carriages(t_game *game)
{
	t_carriage *carriage;

	carriage = game->carriage_head;
	while (carriage)
	{
		//print_single_carriage(carriage);
		if (carriage->remaining_cycle <= 0)
		{
			carriage->statement_index = game->arena[carriage->pc] - 1;
			if (carriage->statement_index > 15 && carriage->statement_index < 0)
			{
				carriage->pc = (carriage->pc + 1) % MEM_SIZE;
			}
			else
			{
				if (g_op_tab[carriage->statement_index].arg_code_type == false ||
					(g_op_tab[carriage->statement_index].arg_code_type == true &&
					get_arg_value(carriage, game->arena) == true))
				{
					if (g_op_tab[carriage->statement_index].f(game, carriage) == false)
						return (false);
					carriage->remaining_cycle = g_op_tab[carriage->statement_index].cycles;
				}
				update_next_statement_pc(carriage);
				if (game->flags_value[FLAG_L] == FO_ADV)
					print_adv(game, carriage, carriage->next_statement_pc - carriage->pc);
			}
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
		/* dump -> end the game */
		if (game->flags_value[FLAG_L] == FO_CYCLES)
			ft_printf("It is not cycle %d\n", game->number_of_cycles + 1);
		if (game->flags_value[FLAG_DUMP] == game->number_of_cycles)
		{
			print_arena(game);
			break;
		}
		run_carriages(game);
		game->number_of_cycles++;
		if (game->cycles_to_die <= 0 || game->number_of_cycles % game->cycles_to_die == 0)
			run_check(game);
		index++;
	}
	return (true);
}

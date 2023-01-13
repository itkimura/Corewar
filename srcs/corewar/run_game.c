/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:18:49 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/14 01:16:59 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void kill_carriage(t_game *game, t_carriage *prev,
				   t_carriage *curr, t_carriage *next)
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
			if (game->flags_value[FLAG_L] == FO_DEATHS)
			{
				ft_printf("live_performed = %d\n", carriage->live_performed);
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
						  carriage->id, game->number_of_cycles - carriage->last_live_performed - 1,
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
	if (game->number_of_live_statement >= NBR_LIVE || (game->number_of_check % MAX_CHECKS == 0 && game->number_of_check != 0))
	{
		game->cycles_to_die = game->cycles_to_die - CYCLE_DELTA;
		game->number_of_check = 0;
	}
	game->number_of_live_statement = 0;
	game->number_of_check++;
}

void print_flag_l_operations(t_carriage *carriage)
{
	int index;

	index = 0;
	ft_printf("P%5d | %s",
			  carriage->id, g_op_tab[carriage->statement_index].name);
	while (index < g_op_tab[carriage->statement_index].nbr_arg)
	{
		ft_putchar(' ');
		if (carriage->arg[index] == T_REG && carriage->statement_index == OP_STI)
		{
			if (carriage->arg[index] == T_REG)
				ft_putchar('r');
			ft_printf("%d ", carriage->arg_value[index]);
			ft_printf("(%d)", carriage->registry[carriage->arg_value[index] - 1]);
		}
		else
		{
			if (carriage->arg[index] == T_REG)
				ft_putchar('r');
			ft_printf("%d", carriage->arg_value[index]);
		}
		index++;
	}
	ft_putchar('\n');
}

void flag_l(t_game *game, t_carriage *carriage)
{
	if (game->flags_value[FLAG_L] == FO_ADV && carriage->statement_index != OP_ZJMP)
		print_adv(game, carriage, carriage->next_statement_pc - carriage->pc);
	if (game->flags_value[FLAG_L] == FO_OPERAIONS)
		print_flag_l_operations(carriage);
}

/*
 * Fix to excute statement after waiting remaining cycle becomes 0
 */
bool run_carriages(t_game *game)
{
	t_carriage *carriage;

	carriage = game->carriage_head;
	// ft_printf("Cycle: %d\n", game->number_of_cycles + 1);
	while (carriage)
	{
		// if (carriage->id == 4)
		// 	ft_printf("remaining: %d, statement_idx: %d\n", carriage->remaining_cycle, carriage->statement_index);
		if (carriage->remaining_cycle <= 0)
		{
			if (carriage->statement_index > 15 || carriage->statement_index < 0)
			{
				// ft_printf("if--------------\n");
				carriage->pc = (carriage->pc + 1) % MEM_SIZE;
				carriage->statement_index = game->arena[carriage->pc] - 1;
				carriage->remaining_cycle = 1;
			}
			else
			{
				// ft_printf("else--------------\n");
				if (get_arg_value(carriage, game->arena) == true)
				{
					// if (carriage->id == 4)
					// 	ft_printf("get_arg_value returns true\n");
					// if (carriage->id == 4)
					// 	print_arg_and_val(carriage);
					if (g_op_tab[carriage->statement_index].f(game, carriage) == false)
						return (false);
				}
				else
				{
					// if (carriage->id == 4)
					// 	ft_printf("get_arg_value returns FALSE\n");
				}
				flag_l(game, carriage);
				// if (carriage->id == 4)
				// 	ft_printf("%spc: %d, next_pc: %d, statement_index: %d%s\n", GREEN, carriage->pc, carriage->next_statement_pc, carriage->statement_index, RESET);
				carriage->pc = carriage->next_statement_pc;
				carriage->statement_index = game->arena[carriage->pc] - 1;
				// if (carriage->id == 4)
				// 	ft_printf("%s statement_idx %d %s\n", RED,carriage->statement_index, RESET);
				if (carriage->statement_index <= 15 && carriage->statement_index >= 0)
					carriage->remaining_cycle = g_op_tab[carriage->statement_index].cycles;
			}
		}
		(carriage->remaining_cycle)--;
		carriage = carriage->next;
	}
	return (true);
}

bool print_dump(t_game *game)
{
	int c;

	c = 0;
	if (game->flags_value[FLAG_DUMP] != INITIAL_VALUE && game->flags_value[FLAG_DUMP] == game->number_of_cycles)
	{
		print_arena(game);
		return (false);
	}
	if (game->flags_value[FLAG_S] != INITIAL_VALUE && game->number_of_cycles % game->flags_value[FLAG_S] == 0 && game->number_of_cycles != 0)
	{
		print_arena(game);
		while (1)
		{
			c = getchar();
			if (c == '\n')
				break;
		}
	}
	return (true);
}

bool run_game(t_game *game)
{
	int index;

	index = 0;
	while (game->carriage_head != NULL)
	{
		if (game->flags_value[FLAG_L] == FO_CYCLES)
			ft_printf("It is now cycle %d\n", game->number_of_cycles + 1);
		if (print_dump(game) == false)
			break;
		if (game->flags_value[FLAG_DUMP] == game->number_of_cycles)
		{
			print_arena(game);
			return (true);
		}
		run_carriages(game);
		game->number_of_cycles++;
		if (game->cycles_to_die <= 0 || game->number_of_cycles % game->cycles_to_die == 0)
		{
			// ft_printf("run check\n");
			run_check(game);
		}
		index++;
	}
	return (true);
}

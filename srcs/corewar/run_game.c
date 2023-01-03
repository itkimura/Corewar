/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:18:49 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/03 16:58:17 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	run_check(t_game *game)
{
	
}


bool	run_carriages(t_carriage *carriage)
{
	int	statement;

	while (carriage)
	{
		if (carriage->remaining_cycle <= 0)
		{
			carriage->statement_code = game->arena[carriage->pc] - 1;
			if (carriage->statement_code > 15 && carriage->statement_code < 0)
			{
				carriage->pc = (carriage->pc + 1) % MEM_SIZE;
			}
			else
			{
				g_op_tab[carriage->statement_code].f(game, c);
				carriage->remaining_cycle = g_op_tab[carriage->statement_code].cycle;
				carriage->pc = carriage->next_statement;
			}
		}
		carriage = carriage->next;
	}
}

bool	run_game(t_game *game)
{
	while (game->carriage_head != NULL)
	{
		/* dump */
		if (game->flags_cvalue[FLAG_DUMP] == game->number_of_cycle)
		{
			print_arena(game);
			break ;
		}
		run_each_carriage(game->carriage_head);
		game->number_of_cycle++;
	}
	return (true);
}

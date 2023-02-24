/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:16:48 by thule             #+#    #+#             */
/*   Updated: 2023/02/23 21:08:49 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	print_dump(t_game *game)
{
	int	c;

	c = 0;
	if (game->flags_value[FLAG_DUMP] != INITIAL_VALUE
		&& game->flags_value[FLAG_DUMP] == game->total_cycles - 1)
	{
		print_arena(game);
		return (false);
	}
	if (game->flags_value[FLAG_S] != INITIAL_VALUE
		&& game->total_cycles % game->flags_value[FLAG_S] == 0
		&& game->total_cycles != 0)
	{
		print_arena(game);
		while (1)
		{
			c = getchar();
			if (c == '\n')
				break ;
		}
	}
	return (true);
}

static void	flag_l_additionals(t_carriage *c)
{
	int	tmp;

	if (c->statement_index == OP_STI
		|| c->statement_index == OP_LDI || c->statement_index == OP_LLDI)
	{
		ft_printf("\n       | ->");
		if (c->statement_index == OP_STI)
		{
			tmp = c->pc + c->arg_value[SECOND_ARG] + c->arg_value[THIRD_ARG];
			ft_printf(" store to %d + %d = %d (with pc and mod %d)",
				c->arg_value[SECOND_ARG], c->arg_value[THIRD_ARG],
				c->arg_value[SECOND_ARG] + c->arg_value[THIRD_ARG],
				c->pc + c->arg_value[SECOND_ARG] + c->arg_value[THIRD_ARG]);
		}
		if (c->statement_index == OP_LDI)
		{
			tmp = c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG] + c->pc;
			ft_printf(" load from %d + %d = %d (with pc and mod %d)",
				c->arg_value[FIRST_ARG], c->arg_value[SECOND_ARG],
				c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG],
				c->pc + c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG]);
		}
		if (c->statement_index == OP_LLDI)
		{
			tmp = c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG] + c->pc;
			ft_printf(" load from %d + %d = %d (with pc %d)",
				c->arg_value[FIRST_ARG], c->arg_value[SECOND_ARG],
				c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG], tmp);
		}
	}
}

static void	print_flag_l_operations(t_carriage *carriage)
{
	int	index;

	index = 0;
	ft_printf("P%5d | %s",
		carriage->id, g_op_tab[carriage->statement_index].name);
	if (carriage->statement_index == OP_FORK)
	{
		ft_printf(" %d (%d)", carriage->arg_value[SECOND_ARG], carriage->arg_value[FIRST_ARG]);
	}
	else
	{
		while (index < g_op_tab[carriage->statement_index].nbr_arg)
		{
			ft_putchar(' ');
			if (carriage->arg[index] == T_REG
				&& ((carriage->arg[index]
						| g_op_tab[carriage->statement_index].arg[index]) == T_REG))
				ft_printf("r%d", carriage->arg_value[index]);
			else
				ft_printf("%d", carriage->arg_value[index]);
			index++;
		}
	}
	if (carriage->statement_index == OP_ZJMP)
	{
		if (carriage->carry == true)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	flag_l_additionals(carriage);
	ft_putchar('\n');
}

void	print_flag_l_death(t_game *game, t_carriage *carriage)
{
	if (game->flags_value[FLAG_L] == FO_DEATHS)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			carriage->id,
			game->total_cycles - carriage->last_live_performed - 1,
			game->cycles_to_die);
}

void	flag_l(t_game *game, t_carriage *carriage)
{
	int	player;

	if (game->flags_value[FLAG_L] == FO_ADV
		&& carriage->statement_index != OP_ZJMP)
		print_adv(game, carriage, carriage->next_statement_pc - carriage->pc);
	if (game->flags_value[FLAG_L] == FO_OPERAIONS)
		print_flag_l_operations(carriage);
	if (game->flags_value[FLAG_L] == FO_LIVES
		&& carriage->statement_index == OP_LIVE)
	{
		player = -(carriage->arg_value[FIRST_ARG]);
		if (player > 0 && player <= game->total_players)
			ft_printf("Player %d (%s) is said to be alive\n",
				player, game->players_in_order[player - 1]->name);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:16:48 by thule             #+#    #+#             */
/*   Updated: 2023/02/26 11:58:38 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	flag_v_additionals(t_carriage *c)
{
	int	tmp;

	ft_printf("\n       | ->");
	if (c->statement_index == OP_STI)
	{
		tmp = c->pc + c->arg_value[SECOND_ARG] + c->arg_value[THIRD_ARG];
		ft_printf(" store to %d + %d = %d (with pc and mod %d)",
			c->arg_value[SECOND_ARG], c->arg_value[THIRD_ARG],
			c->arg_value[SECOND_ARG] + c->arg_value[THIRD_ARG],
			c->pc + c->arg_value[SECOND_ARG] + c->arg_value[THIRD_ARG]);
	}
	else
	{
		tmp = c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG] + c->pc;
		ft_printf(" load from %d + %d = %d ",
			c->arg_value[FIRST_ARG], c->arg_value[SECOND_ARG],
			c->arg_value[FIRST_ARG] + c->arg_value[SECOND_ARG]);
		if (c->statement_index == OP_LDI)
			ft_printf("(with pc and mod %d)", tmp);
		if (c->statement_index == OP_LLDI)
			ft_printf("(with pc %d)", tmp);
	}
}

static void	print_v_normal_operations(t_carriage *carriage)
{
	int	index;

	index = 0;
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

static void	print_flag_v_operations(t_carriage *c)
{
	ft_printf("P%5d | %s", c->id, g_op_tab[c->statement_index].name);
	if (c->statement_index == OP_FORK || c->statement_index == OP_LFORK)
		ft_printf(" %d (%d)",
			c->arg_value[SECOND_ARG], c->arg_value[FIRST_ARG]);
	else
		print_v_normal_operations(c);
	if (c->statement_index == OP_ZJMP)
	{
		if (c->carry == true)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	if (c->statement_index == OP_STI || c->statement_index == OP_LDI
		|| c->statement_index == OP_LLDI)
		flag_v_additionals(c);
	ft_putchar('\n');
}

void	print_flag_v_death(t_game *game, t_carriage *carriage)
{
	if (game->flags_value[FLAG_V] == FO_DEATHS)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			carriage->id,
			game->total_cycles - carriage->last_live_performed - 1,
			game->cycles_to_die);
}

void	flag_v(t_game *game, t_carriage *carriage)
{
	int	player;

	if (game->flags_value[FLAG_V] == FO_OPERAIONS)
		print_flag_v_operations(carriage);
	if (game->flags_value[FLAG_V] == FO_LIVES
		&& carriage->statement_index == OP_LIVE)
	{
		player = -(carriage->arg_value[FIRST_ARG]);
		if (player > 0 && player <= game->total_players)
			ft_printf("Player %d (%s) is said to be alive\n",
				player, game->players_in_order[player - 1]->name);
	}
}

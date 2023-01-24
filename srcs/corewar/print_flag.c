/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:16:48 by thule             #+#    #+#             */
/*   Updated: 2023/01/24 11:24:35 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool print_dump(t_game *game)
{
	int c;

	c = 0;
	if (game->flags_value[FLAG_DUMP] != INITIAL_VALUE && game->flags_value[FLAG_DUMP] == game->total_cycles)
	{
		print_arena(game);
		return (false);
	}
	if (game->flags_value[FLAG_S] != INITIAL_VALUE && game->total_cycles % game->flags_value[FLAG_S] == 0 && game->total_cycles != 0)
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

static void print_flag_l_operations(t_carriage *carriage)
{
	int index;

	index = 0;
	ft_printf("P%5d | %s",
			  carriage->id, g_op_tab[carriage->statement_index].name);
	while (index < g_op_tab[carriage->statement_index].nbr_arg)
	{
		ft_putchar(' ');

		if (carriage->arg[index] == T_REG)
			ft_putchar('r');
		ft_printf("%d", carriage->arg_value[index]);
		if (index == 2 && carriage->statement_index == OP_STI)
			ft_printf("(%d)", carriage->registry[carriage->arg_value[index] - 1]);

		index++;
	}
	if (carriage->statement_index == OP_ZJMP)
	{
		if (carriage->carry == true)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	if (carriage->statement_index == OP_FORK)
	{
		ft_printf(" (%d)", carriage->pc + (carriage->arg_value[FIRST_ARG] % IDX_MOD));
	}
	if (carriage->statement_index == OP_LFORK)
	{
		ft_printf(" (%d)", carriage->pc + (carriage->arg_value[FIRST_ARG]));
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
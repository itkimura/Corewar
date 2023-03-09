/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:16:48 by thule             #+#    #+#             */
/*   Updated: 2023/02/26 12:00:19 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_adv(t_game *game, t_carriage *carriage, int shift)
{
	int	i;
	int	pos;

	i = 0;
	if (shift < 0)
		shift = MEM_SIZE + shift;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ",
		shift, carriage->pc, carriage->pc + shift);
	while (i < shift)
	{
		pos = (carriage->pc + i) % MEM_SIZE;
		ft_printf("%02x ", game->arena[pos]);
		i++;
	}
	ft_printf("\n");
}

void	flag_v_adv(t_game *game, t_carriage *c)
{
	if (game->flags_value[FLAG_V] == FO_ADV
		&& (c->statement_index != OP_ZJMP
			|| (c->statement_index == OP_ZJMP && c->carry == false)))
		print_adv(game, c, c->next_statement_pc - c->pc);
}

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

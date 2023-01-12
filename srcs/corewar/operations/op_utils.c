/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:43:45 by thle              #+#    #+#             */
/*   Updated: 2023/01/12 15:54:07 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool add_carriage(t_game *game, t_carriage *src, unsigned int dst_pc)
{
	t_carriage *dst;

	dst = (t_carriage *) malloc(sizeof(t_carriage));
	if (dst == NULL)
		return (print_error("add_carriage", MALLOC_FAIL), false);
	ft_memcpy(dst, src, sizeof(t_carriage));
	
	dst->id = game->carriage_head->id + 1;
	dst->pc = dst_pc;
	
	dst->next = game->carriage_head;
	game->carriage_head = dst;
	
	dst->statement_index = game->arena[dst_pc] - 1;
	if (dst->statement_index <= 15 && dst->statement_index >= 0)
		dst->remaining_cycle = g_op_tab[dst->statement_index].cycles - 1;
	else
		dst->remaining_cycle = 0;
	return (true);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:33:01 by thule             #+#    #+#             */
/*   Updated: 2023/01/19 16:04:26 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * get value according to the type of the arguments

 * order: which order in carriage->arg/ carrriage->arg_value (eg. SECOND_ARG ...)
 *
 * mod: when arg_type is T_IND
 * 		if  true: mod with IDX_MOD
 *
 * if carriage->arg[order] == T_DIR -> take value from carriage->arg_value[order]
 * if carriage->arg[order] == T_REG -> take value from that reg
 * else take value from address
 *
 */
int	get_value(t_game *game, t_carriage *carriage, int order, bool mod)
{
	int	value;
	int	size;
	int	pos;

	value = carriage->arg_value[order];
	size = 4;
	if (carriage->arg[order] == T_REG)
		value = carriage->registry[carriage->arg_value[order] - 1];
	else if (carriage->arg[order] == T_IND)
	{
		if (carriage->statement_index == OP_LLD)
			size = 2;
		if (mod == true)
			pos = carriage->pc + (carriage->arg_value[order] % IDX_MOD);
		else
			pos = carriage->pc + carriage->arg_value[order];
		if (pos < 0)
			pos = MEM_SIZE + pos;
		value = char_to_int(game->arena, pos % MEM_SIZE, size, true);
	}
	return (value);
}

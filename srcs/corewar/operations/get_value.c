/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:33:01 by thule             #+#    #+#             */
/*   Updated: 2022/12/30 13:38:44 by thule            ###   ########.fr       */
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
 * if carriage->arg[order] == T_IND -> take value from carriage->arg_value[order]
 * if carriage->arg[order] == T_REG -> take value from that reg
 * else take value from address
 * 
 */
int get_value(t_game *game, t_carriage *carriage, int order, bool mod)
{
	int value;

	value = carriage->arg_value[order];
	if (carriage->arg[order] == T_REG)
		value = carriage->registry[carriage->arg_value[order] - 1];
	else if (carriage->arg[order] == T_IND)
	{
		if (mod == true)
			value = reverse_bytes(game->arena,
				(carriage->pc + carriage->arg_value[order] % IDX_MOD) % MEM_SIZE,
				4);
		else
			value = reverse_bytes(game->arena,
				carriage->pc + carriage->arg_value[order] % MEM_SIZE,
				4);
	}
	return value;
}

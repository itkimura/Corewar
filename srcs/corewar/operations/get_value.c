/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:33:01 by thule             #+#    #+#             */
/*   Updated: 2023/01/02 14:08:36 by thle             ###   ########.fr       */
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
	int	size;

	value = carriage->arg_value[order];
	size = 4;
	// if statement is lld
	if (carriage->statement_code == 12)
		size = 2;
	if (carriage->arg[order] == T_REG)
		value = carriage->registry[carriage->arg_value[order] - 1];
	else if (carriage->arg[order] == T_IND)
	{
		if (mod == true)
			value = reverse_bytes(game->arena,
				(carriage->pc + carriage->arg_value[order] % IDX_MOD) % MEM_SIZE,
				size);
		else
			value = reverse_bytes(game->arena,
				carriage->pc + carriage->arg_value[order] % MEM_SIZE,
				size);
	}
	return value;
}

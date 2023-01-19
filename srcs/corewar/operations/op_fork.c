/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:38:53 by thle              #+#    #+#             */
/*   Updated: 2023/01/19 15:43:45 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: fork
 *
 * Info:
 * code:			12 (0c)
 * arg_type_code:	false
 * number of args:	1
 * arguments:		{T_DIR}
 *
 * Tasks:
 * makes a copy of the carriage.
 * What data is being copied?
 * [1]:Values of all registrys
 * [2]:The value of carry
 * [3]:The number of the cycle in which the last statement live performed
 * [4]:And something else, but more on that later.
 * And this copy is placed at the address <FIRST_ARGUMENT> % IDX_MOD.
 * 
 */
bool	op_fork(t_game *game, t_carriage *carriage)
{
	int	pos;

	pos = carriage->pc + (carriage->arg_value[FIRST_ARG] % IDX_MOD);
	if (pos < 0)
		pos = MEM_SIZE + pos;
	if (add_carriage(game, carriage, pos % MEM_SIZE) == false)
		return (false);
	return (true);
}

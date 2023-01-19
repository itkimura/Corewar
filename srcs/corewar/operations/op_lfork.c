/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:39:05 by thle              #+#    #+#             */
/*   Updated: 2023/01/19 15:49:05 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 *
 * Operation: lfork
 *
 * Info:
 * code:			15 (0f)
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
 * And this copy is placed at the address <FIRST_ARGUMENT>.
 * 
 */
bool	op_lfork(t_game *game, t_carriage *carriage)
{
	int	pos;

	pos = carriage->pc + get_value(game, carriage, FIRST_ARG, true);
	if (pos < 0)
		pos = MEM_SIZE + pos;
	if (add_carriage(game, carriage, pos % MEM_SIZE) == false)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:35 by thle              #+#    #+#             */
/*   Updated: 2023/01/02 16:37:23 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
0b11000000 need to shift 6
0b00110000 need to shift 4
0b00001100 need to shift 2
0b00000011 need to shift 0
*/

#define FIRST 0b11000000
#define SECOND 0b00110000
#define THIRD 0b00001100
#define FOURTH 0b00000011
#define IND_VALUE 3

#define T_REG_SIZE 1
#define T_IND_SIZE 2

/*
 * Based on the carriage->arg array, we get the value on the byte code
 */
static bool collect_arg_values(t_carriage *carriage, unsigned char *arena)
{
	int index;
	int current_position;
	int size;

	index = 0;
	current_position = (carriage->pc + 2) % MEM_SIZE;
	while (index < g_op_tab[arena[carriage->pc] - 1].nbr_arg)
	{
		size = 1;
		if (carriage->arg[index] == T_REG)
		{
			carriage->arg_value[index] = arena[current_position];
			if (carriage->arg_value[index] > REG_NUMBER || carriage->arg_value[index] < 1)
				return (false);
		}
		else
		{
			size = T_IND_SIZE;
			if (carriage->arg[index] == T_DIR)
				size = g_op_tab[arena[carriage->pc] - 1].t_dir_size;
			carriage->arg_value[index] = reverse_bytes(arena, current_position, size);
		}
		current_position = (current_position + size) % MEM_SIZE;
		index++;
	}
	carriage->crossed_bytes = current_position;
	return true;
}

// act: argument code type
bool get_arg_value(t_carriage *carriage, unsigned char *arena)
{
	int index;
	int statement_code;
	unsigned char act;

	statement_code = arena[carriage->pc] - 1;
	carriage->statement_code = statement_code;
	act = arena[carriage->pc + 1];
	carriage->arg[0] = (act & FIRST) >> 6;
	carriage->arg[1] = (act & SECOND) >> 4;
	carriage->arg[2] = (act & THIRD) >> 2;
	carriage->arg[3] = (act & FOURTH);
	index = 0;
	while (index < 4)
	{
		if (carriage->arg[index] == IND_VALUE)
			carriage->arg[index] = T_IND;
		if (index >= g_op_tab[statement_code].nbr_arg && carriage->arg[index] != 0)
		{
			return (ft_printf("error in get_arg_value 1\n"), false);
		}
		else if ((carriage->arg[index] & g_op_tab[statement_code].arg[index]) != carriage->arg[index])
			return (ft_printf("error in get_arg_value 2\n"), false);
		index++;
	}
	return (collect_arg_values(carriage, arena));
}

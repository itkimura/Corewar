/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:35 by thle              #+#    #+#             */
/*   Updated: 2023/01/11 14:49:08 by itkimura         ###   ########.fr       */
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
	if (g_op_tab[carriage->statement_index].arg_code_type == false)
		current_position = (carriage->pc + 1) % MEM_SIZE;

	while (index < g_op_tab[arena[carriage->pc] - 1].nbr_arg)
	{
		size = 1;
		if (carriage->arg[index] == T_REG)
		{
			carriage->arg_value[index] = arena[current_position];
			// reg_number check
			if (carriage->arg_value[index] > REG_NUMBER || carriage->arg_value[index] < 1)
				return (false);
		}
		else
		{
			size = T_IND_SIZE;
			if (carriage->arg[index] == T_DIR)
				size = g_op_tab[arena[carriage->pc] - 1].t_dir_size;
			carriage->arg_value[index] = char_to_int(arena, current_position, size);
		}
		current_position = (current_position + size) % MEM_SIZE;
		index++;
	}
	// carriage->next_statement_pc = current_position;
	return (true);
}

void update_next_statement_pc(t_carriage *carriage)
{
	int index;
	int size;

	index = 0;
	size = 0;
	if (g_op_tab[carriage->statement_index].arg_code_type == false)
		carriage->next_statement_pc = (carriage->pc + 1 + g_op_tab[carriage->statement_index].t_dir_size) % MEM_SIZE;
	else
	{
		while (index < 4)
		{
			if (carriage->arg[index] == T_REG)
				size += 1;
			if (carriage->arg[index] == T_DIR)
				size += g_op_tab[carriage->statement_index].t_dir_size;
			if (carriage->arg[index] == T_IND)
				size += T_IND_SIZE;
			index++;
		}
		carriage->next_statement_pc = (carriage->pc + size + 2) % MEM_SIZE;
	}
}

// act: argument code type
bool get_arg_value(t_carriage *carriage, unsigned char *arena)
{
	int index;
	int statement_index;
	unsigned char act;

	statement_index = arena[carriage->pc] - 1;
	carriage->statement_index = statement_index;
	act = arena[carriage->pc + 1];
	if (g_op_tab[carriage->statement_index].arg_code_type == false)
	{
		act = 0b10000000;
	}
	carriage->arg[0] = (act & FIRST) >> 6;
	carriage->arg[1] = (act & SECOND) >> 4;
	carriage->arg[2] = (act & THIRD) >> 2;
	carriage->arg[3] = (act & FOURTH);
	update_next_statement_pc(carriage);
	index = 0;
	while (index < 4)
	{
		if (carriage->arg[index] == IND_VALUE)
			carriage->arg[index] = T_IND;
		if (index >= g_op_tab[statement_index].nbr_arg && carriage->arg[index] != 0)
		{
			return (ft_printf("It should be 0 error in get_arg_value 1\n"), false);
		}
		else if ((carriage->arg[index] & g_op_tab[statement_index].arg[index]) != carriage->arg[index])
			return (ft_printf("error in get_arg_value 2\n"), false);
		index++;
	}
	return (collect_arg_values(carriage, arena));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 17:47:35 by thle              #+#    #+#             */
/*   Updated: 2023/01/23 17:12:22 by thule            ###   ########.fr       */
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

static bool	assign_values(t_carriage *carriage, unsigned char *arena,
							int index, int *current_position)
{
	int	size;

	size = 1;
	if (carriage->arg[index] == T_REG)
	{
		carriage->arg_value[index] = arena[*current_position];
		if (carriage->arg_value[index] > REG_NUMBER
			|| carriage->arg_value[index] < 1)
			return (false);
	}
	else
	{
		size = T_IND_SIZE;
		if (carriage->arg[index] == T_DIR)
			size = g_op_tab[carriage->statement_index].t_dir_size;
		carriage->arg_value[index]
			= char_to_int(arena, *current_position, size, true);
	}
	*current_position = (*current_position + size) % MEM_SIZE;
	return (true);
}

/*
 * Based on the carriage->arg array, we get the value from the arena
 */
static bool	collect_arg_values(t_carriage *carriage, unsigned char *arena)
{
	int	index;
	int	current_position;

	index = 0;
	current_position = (carriage->pc + 2) % MEM_SIZE;
	if (g_op_tab[carriage->statement_index].arg_code_type == false)
		current_position = (carriage->pc + 1) % MEM_SIZE;
	while (index < g_op_tab[carriage->statement_index].nbr_arg)
	{
		if (assign_values(carriage, arena, index, &current_position) == false)
			return (false);
		index++;
	}
	return (true);
}

static void	update_next_statement_pc(t_carriage *carriage)
{
	int	index;
	int	size;

	index = 0;
	size = 0;
	if (g_op_tab[carriage->statement_index].arg_code_type == false)
		carriage->next_statement_pc
			= (carriage->pc + 1
				+ g_op_tab[carriage->statement_index].t_dir_size)
			% MEM_SIZE;
	else
	{
		while (index < g_op_tab[carriage->statement_index].nbr_arg)
		{
			if (carriage->arg[index] == T_REG)
				size += 1;
			if (carriage->arg[index] == T_DIR)
				size += g_op_tab[carriage->statement_index].t_dir_size;
			if (carriage->arg[index] == IND_VALUE)
				size += T_IND_SIZE;
			index++;
		}
		carriage->next_statement_pc = (carriage->pc + size + 2) % MEM_SIZE;
	}
}

static void	get_act(t_carriage *carriage, unsigned char *arena)
{
	int	act;

	act = 0b10000000;
	if (g_op_tab[carriage->statement_index].arg_code_type == true)
		act = arena[(carriage->pc + 1) % MEM_SIZE];
	carriage->arg[0] = (act & FIRST) >> 6;
	carriage->arg[1] = (act & SECOND) >> 4;
	carriage->arg[2] = (act & THIRD) >> 2;
	carriage->arg[3] = (act & FOURTH);
}

bool	get_arg_value(t_carriage *carriage, unsigned char *arena)
{
	int	index;
	int	statement_index;

	index = 0;
	statement_index = carriage->statement_index;
	get_act(carriage, arena);
	update_next_statement_pc(carriage);
	while (index < 4)
	{
		if (carriage->arg[index] == IND_VALUE)
			carriage->arg[index] = T_IND;
		if ((index >= g_op_tab[statement_index].nbr_arg
				&& carriage->arg[index] != 0)
			|| (index < g_op_tab[statement_index].nbr_arg
				&& carriage->arg[index] == 0))
			return (false);
		else if ((carriage->arg[index] & g_op_tab[statement_index].arg[index])
			!= carriage->arg[index])
			return (false);
		index++;
	}
	return (collect_arg_values(carriage, arena));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:31:45 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/27 18:45:47 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* 
 * reverse_bytes
 *
 * read the bytes depending on T_DIR siz, 2 or 4
 * short -> 2 bytes
 * int -> 4 bytes
 */
int	reverse_bytes(t_game *game, unsigned int pc, int nbytes)
{
	unsigned char two_bytes[2];
	unsigned char four_bytes[4];

	if (nbytes == 2)
	{
		two_bytes[0] = game->arena[pc + 1];
		two_bytes[1] = game->arena[pc];
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = game->arena[pc + 3];
		four_bytes[1] = game->arena[pc + 2];
		four_bytes[2] = game->arena[pc + 1];
		four_bytes[3] = game->arena[pc];
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

bool	add_carriage(t_game *game, t_carriage *src, unsigned int dst_pc)
{
	t_carriage *dst;
	int	index;

	if (init_carriage(&dst, game->carriage_head->id + 1) == false)
		return (false);
	dst->carry = src->carry;
	dst->statement_code = src->statement_code;
	dst->last_live_performed = src->last_live_performed;
	dst->remaining_cycle = src->remaining_cycle;
	dst->crossed_bytes = src->crossed_bytes;
	dst->pc = dst_pc;
	index = 0;
	while (index < REG_NUMBER)
	{
	
		dst->registry[index] = src->registry[index];
		index++;
	}
	dst->next = game->carriage_head;
	game->carriage_head = dst;
	return (true);
}

/* 
 * fork:makes a copy of the carriage.
 * And this copy is placed at the address <FIRST_ARGUMENT> % IDX_MOD.
 *
 * What data is being copied?
 * [1]:Values of all registrys
 * [2]:The value of carry
 * [3]:The number of the cycle in which the last statement live performed
 * [4]:And something else, but more on that later.
 *
 * % MEM_SIZE -> if it is 4096 + 3, then 4099 %(4*1024) = 4099 % 4096 = 3.
 */
bool	op_fork(t_game *game, t_carriage *carriage)
{
	int shift;

	shift = reverse_bytes(game, carriage->pc + 1, g_op_tab[12].t_dir_size);
	//shift = reverse_bytes(game, carriage->pc + 1, 2);
	if (add_carriage(game, carriage,
		(unsigned int)(carriage->pc + (shift % IDX_MOD)) % MEM_SIZE) == false)
		return (print_error("op_lfork", MALLOC_FAIL), false);
	carriage->pc += 3; // move position 3 bytes ahead
	carriage->pc %= MEM_SIZE;
	return (true);
}

/* 
 * this statement is similar to the fork statement.
 * Except for the fact that a new carriage is created at the address
 * : current position + <FIRST_ARGUMENT>
 * In the lfork statement, truncation by modulo is not necessary.
 */
bool	op_lfork(t_game *game, t_carriage *carriage)
{
	int shift;

	shift = reverse_bytes(game, carriage->pc + 1, g_op_tab[12].t_dir_size);
	//shift = reverse_bytes(game, carriage->pc, + 1, 2);
	if (add_carriage(game, carriage,
		(unsigned int)(carriage->pc + shift) % MEM_SIZE) == false)
		return (print_error("op_lfork", MALLOC_FAIL), false);
	carriage->pc += 3;
	carriage->pc %= MEM_SIZE;
	return (true);
}

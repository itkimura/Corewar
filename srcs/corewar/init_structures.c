/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:47:45 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/19 14:38:58 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * init game t_game struct
 */
bool init_game(t_game **game)
{
	int index;

	*game = (t_game *)malloc(sizeof(t_game));
	if (*game == NULL)
		return (print_error("init_game", MALLOC_FAIL));
	index = 0;
	while (index < MAX_PLAYERS)
		(*game)->players_in_order[index++] = NULL;
	index = 0;
	while (index < MAX_PLAYERS)
		(*game)->all_players[index++] = NULL;
	index = 0;
	while (index < TOTAL_FLAGS)
		(*game)->flags_value[index++] = 0;
	index = 0;
	while (index < MEM_SIZE)
		(*game)->arena[index++] = 0;
	(*game)->total_players = 0;
	(*game)->total_tmp_players = 0;
	(*game)->cycles_to_die = CYCLE_TO_DIE;
	(*game)->winner = 0;
	(*game)->number_of_cycles = 0;
	(*game)->number_of_live_statement = 0;
	(*game)->number_of_check = 0;
	(*game)->carriage_head = NULL;
	return (true);
}

void	ft_unsigned_char_zero(unsigned char *str, int len)
{
	int	index;

	index = 0;
	while (index < len)
		str[index++] = 0;
}
/*
 * init program structure
 * 1.malloc structure
 * 2.add program into player adday of t_game structure
 */
bool init_program(t_program **new, t_game *game)
{
	*new = (t_program *)malloc(sizeof(t_program));
	if (*new == NULL)
		return (print_error("init_program", MALLOC_FAIL));
	ft_memset(*new, 0, sizeof(t_program));
	// index = 0;
	// while (index < REG_NUMBER)
	// 	(*new)->registry[index++] = 0;
	// // (*new)->pc = 0;
	// (*new)->id = 0;
	// (*new)->carry = false;
	// (*new)->fix_position = false;
	// (*new)->exec_code = NULL;
	// ft_unsigned_char_zero((*new)->comment, COMMENT_LENGTH + 1);
	// ft_unsigned_char_zero((*new)->name, PROG_NAME_LENGTH + 1);
	add_player(*new, game);
	// (*new)->next = NULL;
	return (true);
}

bool init_carriage(t_carriage **new, int id)
{
	*new = (t_carriage *) malloc(sizeof(t_carriage));
	if (*new == NULL)
		return (print_error("init_carriage", MALLOC_FAIL));
	ft_memset(*new, 0, sizeof(t_carriage));
	(*new)->id = id;
	(*new)->registry[0] = -id;
	return (true);
}

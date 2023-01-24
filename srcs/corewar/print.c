/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:28 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/24 15:11:49 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * print error message
 */
bool print_error(char *str, t_error error)
{
	ft_printf("%sError%s: ", RED, RESET);
	if (error == MALLOC_FAIL)
		ft_printf("malloc fail at %s%s%s\n", BOLD, str, RESET);
	else if (error == WRONG_NB)
		ft_printf("wrong input number for %s%s%s\n", BOLD, str, RESET);
	else if (error == OPEN_FAIL)
		ft_printf("cannot open %s%s%s file\n", BOLD, str, RESET);
	else if (error == DUP_PLAYER_NB)
		ft_printf("duplication of player number %s%s%s\n", BOLD, str, RESET);
	else if (error == NO_PLAYER_AFTER_FLAG_N)
		ft_printf("the input after %s-n N%s should be a player\n", BOLD, RESET);
	else if (error == MISSING_PLAYER)
		ft_printf("Player %s%s%s is missing\n", BOLD, str, RESET);
	else if (error == TOO_MANY_PLAYERS)
		ft_printf("Too many players\n");
	else if (error == INVALID_HEADER)
		ft_printf("File %s%s%s has invalid magic header\n", BOLD, str, RESET);
	else if (error == INVALID_NULL)
		ft_printf("File %s%s%s has invalid null bytes\n", BOLD, str, RESET);
	else if (error == INVALID_CHAMPION_SIZE)
		ft_printf("File %s%s%s has too large champion size\n", BOLD, str, RESET);
	else if (error == INVALID_CHAMPION_SIZE)
		ft_printf("File %s%s%s has extra champion code\n", BOLD, str, RESET);
	return (false);
}

void bold(char *str1, char *str2)
{
	ft_printf("%s%s%s%s", BOLD, str1, RESET, str2);
}
/*
 * print help function
 */
void print_help(char *file_path)
{
	bold("Name", "\n");
	// ft_printf("%sName\n\t%s%s", BOLD, file_path, RESET);
	ft_printf("\t - is a player that the progress of the battle and");
	ft_printf(" declare the winner champion after its completion\n\n");
	bold("Help", "\n\t");
	bold(file_path, "\tNO INPUT - print this help message\n\n");
	bold("Usage", "\n\t");
	bold(file_path, "\t[-d N | -n N] <champion1.cor> <...>\n");
	bold("Flag", "\n");
	bold("\t[-d / -dump N]", ":\tDump memory (32 octets·per·line) after");
	bold("N", "cycles and exit\n");
	bold("\t[-s N]", ":\t\tDump memory (32 octets per line) every");
	bold("N", " cycles, pause and repeat again when 'enter' pressed\n");
	bold("\t[-n N]", ":\t\tSet %sN%s of the next player\n");
	bold("\t[-l N]", ":\n");
	bold("\t\t\t1  ", ":Show lives\n");
	bold("\t\t\t2  ", ":Show the number of cycles\n");
	bold("\t\t\t4  ", ":Show operations (Params )\n");
	bold("\t\t\t8  ", ":Show death\n");
	bold("\t\t\t16 ", ":Show PC movement (Except for jumps)\n\n");
	bold("\t[-a]:", ":\t\tPrint output from \"%saff%s\"\n\n");
}

void print_adv(t_game *game, t_carriage *carriage, int shift)
{
	int i;

	i = 0;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", shift, carriage->pc, carriage->pc + shift);
	while (i < shift)
		ft_printf("%02x ", game->arena[carriage->pc + i++]);
	ft_printf("\n");
}

/*
 * print arena
 */
void print_arena(t_game *game)
{
	int index;

	index = 0;
	while (index < MEM_SIZE)
	{
		// if (index == 2435 || index == 2440)
		// 	ft_printf("%s", GREEN);
		if ((index) % 64 == 0)
			ft_printf("0x%04x : ", index);
		ft_printf("%02x ", game->arena[index]);
		if ((index + 1) % 64 == 0)
			ft_printf("\n");
		// ft_printf("%s", RESET);
		index++;
	}
}

/*
 * Debug printing function
 */
void print_single_player(t_player *player)
{
	ft_printf("[%s%s%s]\n", BOLD, player->name, RESET);
	ft_printf("%sregistry:\t\n", BOLD, RESET);
	ft_printf("%sexec_code_size%s:\t%d\n", BOLD, RESET, player->exec_code_size);
	ft_printf("%scomment%s:\t%s\n", BOLD, RESET, player->comment);
	if (player->exec_code != NULL)
	{
		ft_printf("%sexec_code%s:\t", BOLD, RESET);
		for (unsigned int i = 0; i < player->exec_code_size; i++)
			ft_printf("%02x ", player->exec_code[i]);
	}
	ft_printf("\n");
}

/*
 * Debug printing function
 */
void print_all_players(t_game *game)
{
	int index;
	t_player **p;

	index = 0;
	p = game->all_players;
	while (index < MAX_PLAYERS)
	{
		if (p[index] != NULL)
			print_single_player(p[index]);
		index++;
	}
}

/*
 * print single carriage
 */
void print_single_carriage(t_carriage *head)
{
	for (int i = 0; i < REG_NUMBER; i++)
		ft_printf("%s\t[%d]%s:%d\n", BOLD, i, RESET, head->registry[i]);
	ft_printf("\n");
	ft_printf("%sid:%s\t%u\n", BOLD, RESET, head->id);
	ft_printf("%scarry%s:\t%d\n", BOLD, RESET, head->carry);
	ft_printf("%sstatement_index%s:\t%d\n", BOLD, RESET, head->statement_index);
	ft_printf("%sremaining_cycle%s:\t%d\n", BOLD, RESET, head->remaining_cycle);
	ft_printf("%spc%s:\t%d\n", BOLD, RESET, head->pc);
	ft_printf("%snext_statment_pc%s:\t%d\n", BOLD, RESET, head->next_statement_pc);
	for (int i = 0; i < 4; i++)
		ft_printf("arg[%d]:\t%d\n", i, head->arg[i]);
	for (int i = 0; i < 4; i++)
		ft_printf("arg_value[%d]:\t%d\n", i, head->arg_value[i]);
}

/*
 * print carriage linked list*
 */
void print_carriage_list(t_carriage *head)
{
	while (head)
	{
		print_single_carriage(head);
		head = head->next;
	}
}

/*
 * Debug printing t_game function
 */

char *flag_name(int nb)
{
	if (nb == FLAG_N)
		return ("-n");
	if (nb == FLAG_DUMP)
		return ("-d");
	if (nb == FLAG_V)
		return ("-v");
	if (nb == FLAG_A)
		return ("-a");
	return (NULL);
}

void print_game(t_game *game)
{
	if (game != NULL)
	{
		ft_printf("[%st_game%s]\n", BOLD, RESET);
		ft_printf("%stotal_players%s:\t\t%d\n", BOLD, RESET, game->total_players);
		ft_printf("%scycle_to_die%s:\t\t%d\n", BOLD, RESET, game->cycles_to_die);
		// ft_printf("%stotal_tmp_players%s:\t%d\n", BOLD, RESET, game->total_tmp_players);
		ft_printf("%splayers_in_order:\t\n", BOLD, RESET);
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (game->players_in_order[i])
				ft_printf("%s\t[%d]%s:\t%s\n", BOLD, i, RESET, game->players_in_order[i]->name);
		}
		ft_printf("%sall_players:\t\n", BOLD, RESET);
		for (int i = 0; i < MAX_PLAYERS; i++)
		{
			if (game->all_players[i])
				ft_printf("%s\t[%d]%s:\t%s\tfix_position:\t*d\n", BOLD, i, RESET, game->all_players[i]->name, game->all_players[i]->fix_position);
		}
		ft_printf("%sflags_value:\t\n", BOLD, RESET);
		for (int i = 0; i < TOTAL_FLAGS; i++)
			ft_printf("%s\t[%s]%s:\t%d\n", BOLD, flag_name(i), RESET, game->flags_value[i]);
		ft_printf("\n");
	}
}

/*
 * Print bits to debug numbers.
 */
void print_bits(unsigned int nbr, int size)
{
	ft_printf("%lu: ", nbr);
	for (int bit = size - 1; bit >= 0; bit--)
	{
		if (((nbr >> bit) & 1) == 0)
			ft_printf("0 ");
		else
			ft_printf("1 ");
		if (bit % 4 == 0)
			ft_printf("  ");
	}
	ft_printf("\n");
}

/*
 * print arguments and their value
 */
void print_arg_and_val(t_carriage *carriage)
{
	ft_printf("%s%s%s%s:", BOLD, GREEN, g_op_tab[carriage->statement_index].name, RESET);
	for (int i = 0; i < g_op_tab[carriage->statement_index].nbr_arg; i++)
	{
		if (carriage->arg[i] == T_REG)
			ft_printf("\t[%d] - %s - %d\n", i + 1, "T_REG", carriage->arg_value[i]);
		else if (carriage->arg[i] == T_DIR)
			ft_printf("\t[%d] - %s - %d\n", i + 1, "T_DIR", carriage->arg_value[i]);
		else if (carriage->arg[i] == T_IND)
			ft_printf("\t[%d] - %s - %d\n", i + 1, "T_IND", carriage->arg_value[i]);
		else
			ft_printf("\t[%d] - %s - %d\n", i + 1, "NOTHING", carriage->arg_value[i]);
	}
}

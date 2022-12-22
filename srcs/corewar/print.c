/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:28 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/22 11:35:52 by itkimura         ###   ########.fr       */
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

/*
 * print help function
 */
void print_help(char *file_path)
{
	ft_printf("%sName\n\t%s%s", BOLD, file_path, RESET);
	ft_printf(" - is a player that the progress of the battle and");
	ft_printf(" declare the winner champion after its completion\n\n");
	ft_printf("%sHELP\n\t%s%s NO INPUT - ", BOLD, file_path, RESET);
	ft_printf("print this help message\n\n");
	ft_printf("%sUsage\n\t%s%s [-d N | -n N]", BOLD, file_path, RESET);
	ft_printf(" <champion1.cor> <...>\n\n");
	ft_printf("%sFlag%s\n", BOLD, RESET);
	ft_printf("\t%s-d N%s\tDump memory (32 octets per line) after", BOLD, RESET);
	ft_printf(" %sN%s cycles and exit\n", BOLD, RESET);
	ft_printf("\t%s-n N%s\t", BOLD, RESET);
	ft_printf("Set %sN%s of the next player\n\n", BOLD, RESET);
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
	ft_printf("%sstatement_code%s:\t%d\n", BOLD, RESET, head->statement_code);
	ft_printf("%slast_live_performed%s:\t%d\n", BOLD, RESET, head->last_live_performed);
	ft_printf("%sremaining_cycle%s:\t%d\n", BOLD, RESET, head->remaining_cycle);
	ft_printf("%spc%s:\t%d\n", BOLD, RESET, head->pc);
	ft_printf("%scrossed_bytes%s:\t%d\n", BOLD, RESET, head->crossed_bytes);
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
	return (NULL);
}

void print_game(t_game *game)
{
	if (game != NULL)
	{
		ft_printf("[%st_game%s]\n", BOLD, RESET);
		ft_printf("%stotal_players%s:\t\t%d\n", BOLD, RESET, game->total_players);
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
void print_bits(uint32_t nbr, int size)
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

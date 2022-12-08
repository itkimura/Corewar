/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:28 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 17:07:36 by thle             ###   ########.fr       */
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
	else if (error == INVALID_HEADER)
		ft_printf("File %s%s%s has invalid magic header\n", BOLD, str, RESET);
	else if (error == INVALID_NULL)
		ft_printf("File %s%s%s has invalid null bytes\n", BOLD, str, RESET);
	else if (error == INVALID_CHAMPION_SIZE)
		ft_printf("File %s%s%s has too large champion size\n", BOLD, str, RESET);
	return (false);
}

/*
 * print help function
 */
void print_help(char *file_path)
{
	ft_printf("%sName\n\t%s%s", BOLD, file_path, RESET);
	ft_printf(" - is a program that the progress of the battle and");
	ft_printf(" declare the winner champion after its completion\n\n");
	ft_printf("%sHELP\n\t%s%s NO INPUT - ", BOLD, file_path, RESET);
	ft_printf("print this help message\n\n");
	ft_printf("%sUsage\n\t%s%s [-d N | -n N]", BOLD, file_path, RESET);
	ft_printf(" <champion1.cor> <...>\n\n");
	ft_printf("%sFlag%s\n", BOLD, RESET);
	ft_printf("\t%s-d N%s\tDump memory (32 octets per line) after", BOLD, RESET);
	ft_printf(" %sN%s cycles and exit\n", BOLD, RESET);
	ft_printf("\t%s-n N%s\t", BOLD, RESET);
	ft_printf("Set %sN%s of the next player\n", BOLD, RESET);
}

/*
 * Debug printing function
 */
void print_program(t_program *program)
{
	ft_printf("[%s%s%s]\n", BOLD, program->name, RESET);
	ft_printf("%sregistry:\t\n", BOLD, RESET);
	for (int i = 0; i < 16; i++)
		ft_printf("%s\t[%d]%s:%d\n", BOLD, i, RESET, program->registry[i]);
	ft_printf("\n");
	ft_printf("%spc:\t%d\n", BOLD, RESET, program->pc);
	ft_printf("%scarry%s:\t%d\n", BOLD, RESET, program->carry);
	ft_printf("%sfix_postion%s:\t%d\n", BOLD, RESET, program->fix_position);
	ft_printf("%sexec_code_size%s:\t%d\n", BOLD, RESET, program->exec_code_size);
	ft_printf("%scomment%s:\t%s\n", BOLD, RESET, program->comment);
	if (program->exec_code != NULL)
	{
		ft_printf("%sexec_code%s:\t", BOLD, RESET);
		for (unsigned int i = 0; i < program->exec_code_size; i++)
			ft_printf("%02x ", program->exec_code[i]);
	}
	ft_printf("\n");
}

/*
 * Debug printing t_game function
 */
void print_game(t_game *game)
{
	if (game != NULL)
	{
		ft_printf("[%st_game%s]\n", BOLD, RESET);
		ft_printf("%stotal_players%s:\t%d\n", BOLD, RESET, game->total_players);
		ft_printf("%splayer_array:\t\n", BOLD, RESET);
		for (int i = 0; i < MAX_PLAYERS; i++)
			ft_printf("%s\t[%d]%s:\t%d\n", BOLD, i, RESET, game->player_array[i]);
		ft_printf("%sflags_value:\t\n", BOLD, RESET);
		for (int i = 0; i < TOTAL_FLAGS; i++)
			ft_printf("%s\t[%d]%s:\t%d\n", BOLD, i, RESET, game->flags_value[i]);
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

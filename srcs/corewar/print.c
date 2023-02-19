/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:28 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/25 15:33:40 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	bold(char *str1, char *str2)
{
	ft_printf("%s%s%s%s", BOLD, str1, RESET, str2);
}

/*
 * print error message
 */
bool	print_error(char *str, t_error error)
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
void	print_help(char *file_path)
{
	bold("Name", "\n");
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

void	print_adv(t_game *game, t_carriage *carriage, int shift)
{
	int	i;

	i = 0;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ",
		shift, carriage->pc, carriage->pc + shift);
	while (i < shift)
		ft_printf("%02x ", game->arena[carriage->pc + i++]);
	ft_printf("\n");
}

/*
 * print arena
 */
void	print_arena(t_game *game)
{
	int	index;

	index = 0;
	while (index < MEM_SIZE)
	{
		if ((index) % 64 == 0)
			ft_printf("0x%04x : ", index);
		ft_printf("%02x ", game->arena[index]);
		if ((index + 1) % 64 == 0)
			ft_printf("\n");
		index++;
	}
}

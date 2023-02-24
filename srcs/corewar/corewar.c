/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:56 by thle              #+#    #+#             */
/*   Updated: 2023/02/23 21:52:55 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * 1.initiarize game structure
 *
 * [while loop each argv]
 * 1.if it is flag, save value into game->flag_value
 * 2.if it is a player name, validate the champion.
 * 3.Call update_players_array to give the correct Player number
 */
bool	validate_argv(int argc, char **argv)
{
	int		flag;
	int		index;
	t_game	*game;

	game = NULL;
	if (init_game(&game) == false)
		return (free_all(game), false);
	flag = -1;
	index = 1;
	while (index < argc)
	{
		if (which_flag(argv, &index, &flag, game) == false)
			return (free_all(game), false);
		if (flag == NOT_FLAG)
			if (validate_champion(argv[index], game) == false)
				return (free_all(game), false);
		index++;
	}
	if (game->total_players == 0)
		return (print_help(), free_all(game), true);
	if (update_players_array(game) == false)
		return (free_all(game), false);
	init_arena(game);
	run_game(game);
	return (free_all(game), true);
}

/*
 * Check the number of args, and it is only one print help text
 * if there are some arguments, start validation.
 *
 * Error occured -> return (1);
 */
int	main(int argc, char *argv[])
{
	if (argc < 2)
		print_help();
	else
	{
		if (validate_argv(argc, argv) == false)
			return (1);
	}
	return (0);
}

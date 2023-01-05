/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:56 by thle              #+#    #+#             */
/*   Updated: 2023/01/05 15:39:01 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/corewar.h"

/*
 * initialize arena, place players onto arena
 * also print announcement of players
 */
void init_arena(t_game *game)
{
	int index;
	int max_memory;
	int position;
	t_player *player;

	max_memory = MEM_SIZE / game->total_players;
	index = 0;
	position = 0;
	ft_printf("Introducing contestants...\n");
	game->winner = game->total_players;
	while (index < game->total_players)
	{
		player = game->players_in_order[index];
		ft_memcpy(game->arena + position,
				  game->players_in_order[index]->exec_code,
				  game->players_in_order[index]->exec_code_size);
		player->carriage->pc = position;
		position += max_memory;
		ft_printf("* Player %d, ", index + 1, player->exec_code_size);
		ft_printf("weighing %d bytes, ", player->exec_code_size);
		ft_printf("\"%s\" (\"%s\") !\n", player->name, player->comment);
		index++;
	}
}

/*
 * 1.initiarize game structure
 *
 * [while loop each argv]
 * 1.if it is flag, save value into game->flag_value
 * 2.if it is a player name, validate the champion.
 * 3.Call update_players_array to give the correct Player number
 */
bool validate_argv(int argc, char **argv)
{
	int flag;
	int index;
	t_game *game;

	game = NULL;
	if (init_game(&game) == false)
		return (free_all(game), false);
	ft_printf("---- print_game ----\n");
	print_game(game);
	flag = -1;
	index = 1;
	while (index < argc)
	{
		if (which_flag(argv, &index, &flag, game) == false)
			return (free_all(game), false);
		if (flag == NOT_FLAG)
		{
			if (validate_champion(argv[index], game) == false)
				return (free_all(game), false);
		}
		index++;
	}
	if (update_players_array(game) == false)
		return (free_all(game), false);
	init_arena(game);
	//print_all_players(game);
	// print_arena(game);
	ft_printf("---- print_all_player ----\n");
	print_all_players(game);
	ft_printf("---- print_game ----\n");
	print_game(game);
	run_game(game);

	/* to be deleted */
	// ft_printf("---- print_carriage ----\n");
	// print_carriage_list(game->carriage_head);
	//ft_printf("---- before ----\n");
	//print_carriage_list(game->carriage_head);
	//print_arena(game);
	//game->carriage_head->pc = 5;
	// ft_printf("---- test_op ----\n");
	// game->carriage_head->registry[1] = 42;
	// op_aff(game, game->carriage_head);
	// ft_printf("---- after ----\n");
	// print_carriage_list(game->carriage_head);
	free_all(game);
	return (true);
}

/*
 * Check the number of args, and it is only one print help text
 * if there are some arguments, start validation.
 *
 * Error occured -> return (1);
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
		print_help(argv[0]);
	else
	{
		if (validate_argv(argc, argv) == false)
			return (1);
	}
	return (0);
}

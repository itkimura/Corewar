/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:56 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 17:07:35 by thle             ###   ########.fr       */
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
		return (false);
	index = 0;
	while (index < MAX_PLAYERS)
		(*game)->player_array[index++] = NULL;
	index = 0;
	while (index < TOTAL_FLAGS)
		(*game)->flags_value[index++] = 0;
	(*game)->total_players = 0;
	return (true);
}

/*
 *
 */
bool validate_player_nb(t_program *new, t_game *game)
{
	int player_nb;

	(void)new;
	(void)game;
	(void)player_nb;
	ft_printf("here\n");
	if (game->flags_value[FLAG_N])
	{
		player_nb = game->flags_value[FLAG_N];
		if (game->player_array[player_nb] == NULL || game->player_array[player_nb]->fix_position == true)
			return (print_error(ft_itoa(player_nb), DUP_PLAYER_NB));
	}
	else
	{
		player_nb = game->total_players;
		while (game->player_array[player_nb]->fix_position == true)
			player_nb++;
	}
	new->registry[0] = -1 * player_nb;
	game->flags_value[FLAG_N] = 0;
	game->total_players++;
	return (true);
}

/*
 * init program structure
 * 1.malloc structure
 * 2.validate and store player number
 *
 */
bool init_program(t_program **new, t_game *game)
{
	*new = (t_program *)malloc(sizeof(t_program));
	if (*new == NULL)
		return (print_error("init_program", MALLOC_FAIL));
	if (validate_player_nb(*new, game))
		return (false);
	// print_program(*new);
	return (true);
	// Check if flag_value[Flag_n] -> t_program new, new.r[0] = flag_value[FLAG_N];
	// flag_value[flag_n] = 0;
}

/*
 * store_player number
 * if game->flag_value[FLAG_N] != 0 -> program->registry[0]
 * Check game->player_array[nb] != 0) -> swap and put into the next one
 *
 * else
 *  program->registory[total_players] = program;
 *  total_players++;
void store_palyer_number(t_game *game, t_program *program)
{

}
*/

/*
 * 1. open -> if it's fail, it means the file is not exist.
 * 1. Make program structure
 * 2. Start reading and save info into program
 */
bool validate_champion(char *file_path, t_game *game)
{
	int fd;
	t_program *new;

	new = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_error(file_path, OPEN_FAIL));
	if (init_program(&new, game) == false)
		return (false);
	// read then validate
	close(fd);
	return (true);
}

/*
 * 1.initiarize game structure
 * 2.Check if argv is directory
 */
bool validate_argv(int argc, char **argv)
{
	int flag;
	int index;
	t_game *game;

	game = NULL;
	if (init_game(&game) == false)
		return (print_error("init_game", MALLOC_FAIL));
	flag = -1;
	index = 1;
	while (index < argc)
	{
		ft_printf("---- %s ----\n", argv[index]);
		print_game(game);
		if (which_flag(argv, &index, &flag, game) == false)
			return (false);
		if (flag == NOT_FLAG)
		{
			if (validate_champion(argv[index], game) == false)
				return (false);
		}
		flag = NOT_FLAG;
		index++;
	}
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
	// Branch 'vm' set up to track remote branch 'vm' from 'origin'.
	// ./corewar [-dump nbr_cycles] [[-n number] champion1.cor]
	if (argc < 2)
		print_help(argv[0]);
	else
	{
		if (validate_argv(argc, argv) == false)
			return (1);
	}
	return (0);
}

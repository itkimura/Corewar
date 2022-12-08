/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:56 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 16:16:47 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* 
 * init game t_game struct
 */
t_bool	init_game(t_game **game)
{
	int		index;

	*game = (t_game *)malloc(sizeof(t_game));
	if (*game == NULL)
		return (FALSE);
	index = 0;
	while (index < MAX_PLAYERS)
		(*game)->player_array[index++] = NULL;
	index = 0;
	while (index < TOTAL_FLAGS)
		(*game)->flags_value[index++] = 0;
	(*game)->total_players = 0;
	return (TRUE);
}

/*
 * 
 */
t_bool validate_player_nb(t_program *new, t_game *game)
{
	int	player_nb;

	(void)new;
	(void)game;
	(void)player_nb;
	ft_printf("here\n");
	if (game->flags_value[FLAG_N])
	{
		player_nb = game->flags_value[FLAG_N];
		if (game->player_array[player_nb] == NULL || game->player_array[player_nb]->fix_position == TRUE)
			return (print_error(ft_itoa(player_nb), DUP_PLAYER_NB));
	}
	else
	{
		player_nb = game->total_players;
		while (game->player_array[player_nb]->fix_position == TRUE)
			player_nb++;
	}
	new->registry[0] = -1 * player_nb;
	game->flags_value[FLAG_N] = 0;
	game->total_players++;
	return (TRUE);
}

/*
 * init program structure
 * 1.malloc structure
 * 2.validate and store player number
 * 
 */
t_bool init_program(t_program **new, t_game *game)
{
	*new = (t_program *)malloc(sizeof(t_program));
	if (*new == NULL)
		return (print_error("init_program", MALLOC_FAIL));
	if (validate_player_nb(*new, game))
		return (FALSE);
	//print_program(*new);
	return (TRUE);
	//Check if flag_value[Flag_n] -> t_program new, new.r[0] = flag_value[FLAG_N];
	//flag_value[flag_n] = 0;
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
t_bool validate_champion(char *file_path, t_game *game)
{
	int fd;
	t_program *new;

	new = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_error(file_path, OPEN_FAIL));
	if (init_program(&new, game) == FALSE)
		return (FALSE);
	// read then validate
	close(fd);
	return (TRUE);
}

/*
 * 1.initiarize game structure
 * 2.Check if argv is directory
*/
t_bool validate_argv(int argc, char **argv)
{
	int		flag;
	int		index;
	t_game	*game;

	game = NULL;
	if (init_game(&game) == FALSE)
		return (print_error("init_game", MALLOC_FAIL));
	flag = -1;
	index = 1;
	while (index < argc)
	{
		ft_printf("---- %s ----\n", argv[index]);
		print_game(game);
		if (which_flag(argv, &index, &flag, game) == FALSE)
			return (FALSE);
		if (flag == NOT_FLAG)
		{
			if (validate_champion(argv[index], game) == FALSE)
				return (FALSE);
		}
		flag = NOT_FLAG;
		index++;
	}
	return (TRUE);
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
		if (validate_argv(argc, argv) == FALSE)
			return (1);
	}
	return (0);
}

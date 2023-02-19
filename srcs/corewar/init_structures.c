/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:47:45 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/25 09:34:44 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * init game t_game struct
 */
bool	init_game(t_game **game)
{
	int	index;

	*game = (t_game *)malloc(sizeof(t_game));
	if (*game == NULL)
		return (print_error("init_game", MALLOC_FAIL));
	ft_memset(*game, 0, sizeof(t_game));
	index = 0;
	while (index < TOTAL_FLAGS)
		(*game)->flags_value[index++] = INITIAL_VALUE;
	(*game)->cycles_to_die = CYCLE_TO_DIE;
	(*game)->check_counter = CYCLE_TO_DIE;
	(*game)->total_cycles = 1;
	return (true);
}

/*
 * init player structure
 * 1.malloc structure
 * 2.add player into player adday of t_game structure
 */
bool	init_player(t_player **new, t_game *game)
{
	*new = (t_player *)malloc(sizeof(t_player));
	if (*new == NULL)
		return (print_error("init_player", MALLOC_FAIL));
	ft_memset(*new, 0, sizeof(t_player));
	add_player(*new, game);
	return (true);
}

bool	init_carriage(t_carriage **new, t_player *player, int id)
{
	(void)player;
	*new = (t_carriage *)malloc(sizeof(t_carriage));
	if (*new == NULL)
		return (print_error("init_carriage", MALLOC_FAIL));
	ft_memset(*new, 0, sizeof(t_carriage));
	(*new)->id = id;
	(*new)->registry[0] = -id;
	(*new)->next = NULL;
	return (true);
}

/*
 * initialize arena, place players onto arena
 * also print announcement of players
 */
void	init_arena(t_game *game)
{
	int			index;
	int			max_memory;
	int			position;
	t_player	*player;

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

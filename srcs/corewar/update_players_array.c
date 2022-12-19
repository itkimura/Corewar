/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_players_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:03:25 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/19 13:23:52 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * add program into player array of t_game structure
 * if "-n" option is active, put the program into game->players array.
 * if not, put program game->all_players array.
 */
bool	add_player(t_program *new, t_game *game)
{
	int	player_nb;

	if (game->total_players >= MAX_PLAYERS)
		return (print_error("", WRONG_NB));
	if (game->flags_value[FLAG_N])
	{
		player_nb = game->flags_value[FLAG_N] - 1;
		if (game->players_in_order[player_nb] != NULL)
			return (print_error(ft_itoa(player_nb), DUP_PLAYER_NB));
		game->players_in_order[player_nb] = new;
		new->fix_position = true;
		game->flags_value[FLAG_N] = 0;
	}
	game->all_players[game->total_players++] = new;
	return (true);
}

/*
 * add players from all_payers array to players_in_order array
 *
 * i -> index to loop all_players array
 * j -> index to loop players_in_order array
 */
void	align_players(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->total_players)
	{
		if (game->all_players[i] != NULL)
		{
			if (game->all_players[i]->fix_position == false)
			{
				while (game->players_in_order[j] != NULL)
					j++;
				game->players_in_order[j] = game->all_players[i];
			}
		}
		i++;
	}
}

/*
 * Call "align_players" to add players from all_payers array to players array
 * while loop -> check if any players missing and set registry[0]
 */
bool	update_players_array(t_game *game)
{
	int		index;
	t_program *prev;

	align_players(game);
	index = game->total_players - 1;;
	ft_printf("here\n");
	while (index >= 0)
	{
		if (game->players_in_order[index] == NULL)
			return (print_error(ft_itoa(index + 1), MISSING_PLAYER));
		if (index == game->total_players - 1)
			game->carriage_head = game->players_in_order[index];
		else
			prev->next = game->players_in_order[index];
		prev = game->players_in_order[index];
		game->players_in_order[index]->registry[0] = -1 * (index + 1);
		game->players_in_order[index]->id = index + 1;
		index--;
	}
	return (true);
}

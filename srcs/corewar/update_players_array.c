/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_players_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:03:25 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/24 11:03:26 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * add player into player array of t_game structure
 * if "-n" option is active, put the player into game->players array.
 * if not, put player game->all_players array.
 */
bool	add_player(t_player *new, t_game *game)
{
	int	player_nb;

	if (game->total_players >= MAX_PLAYERS)
		return (print_error("", WRONG_NB));
	if (game->flags_value[FLAG_N] != -1)
	{
		player_nb = game->flags_value[FLAG_N] - 1;
		if (game->players_in_order[player_nb] != NULL)
			return (print_error(ft_itoa(player_nb), DUP_PLAYER_NB));
		game->players_in_order[player_nb] = new;
		new->fix_position = true;
		game->flags_value[FLAG_N] = -1;
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
	int			index;
	char		missing_player[2];
	t_carriage	*prev;
	t_carriage	*new;

	missing_player[1] = '\0';
	align_players(game);
	index = game->total_players - 1;
	game->total_carriages = game->total_players;
	while (index >= 0)
	{
		missing_player[0] = index + 1 + '0';
		if (game->players_in_order[index] == NULL)
			return (print_error(missing_player, MISSING_PLAYER));
		if (init_carriage(&new,
				game->players_in_order[index], index + 1) == false)
			return (false);
		if (index == game->total_players - 1)
			game->carriage_head = new;
		else
			prev->next = new;
		prev = new;
		game->players_in_order[index]->carriage = new;
		index--;
	}
	return (true);
}

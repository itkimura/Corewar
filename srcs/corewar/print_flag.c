/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:16:48 by thule             #+#    #+#             */
/*   Updated: 2023/02/24 11:12:34 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool	print_dump(t_game *game)
{
	int	c;

	c = 0;
	if (game->flags_value[FLAG_DUMP] != INITIAL_VALUE
		&& game->flags_value[FLAG_DUMP] == game->total_cycles - 1)
	{
		print_arena(game);
		return (false);
	}
	if (game->flags_value[FLAG_S] != INITIAL_VALUE
		&& game->total_cycles % game->flags_value[FLAG_S] == 0
		&& game->total_cycles != 0)
	{
		print_arena(game);
		while (1)
		{
			c = getchar();
			if (c == '\n')
				break ;
		}
	}
	return (true);
}

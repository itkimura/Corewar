/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:42:25 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/12 17:31:19 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void	free_program(t_program *p)
{
	if (p != NULL)
	{
		if (p->exec_code != NULL)
			free(p->exec_code);
		p->exec_code = NULL;
		free(p);
		p = NULL;
	}
}

void	free_game(t_game *game)
{
	int	index;

	if (game != NULL)
	{
		index = 0;
		while (index < MAX_PLAYERS)
		{
			if (game->all_players[index] != NULL)
				free_program(game->all_players[index]);
			index++;
		}
		free(game);
	}
}

void	free_all(t_game *game)
{
	free_game(game);
}

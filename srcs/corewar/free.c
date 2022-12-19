/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:42:25 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/19 14:55:37 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void free_program(t_program *p)
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

void free_carriages(t_carriage *head)
{
	t_carriage *next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

void free_game(t_game *game)
{
	int index;

	if (game != NULL)
	{
		index = 0;
		while (index < MAX_PLAYERS)
		{
			if (game->all_players[index] != NULL)
			{
				ft_printf("%d here\n", index);
				free_program(game->all_players[index]);
			}
			index++;
		}
		free_carriages(game->carriage_head);
		free(game);
	}
}

void free_all(t_game *game)
{
	// print_all_programs(game);
	free_game(game);
}

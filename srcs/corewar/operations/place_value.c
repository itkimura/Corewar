/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:27:30 by thle              #+#    #+#             */
/*   Updated: 2023/01/19 16:03:24 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define FIRST 0xFF000000
#define SECOND 0x00FF0000
#define THIRD 0x0000FF00
#define FOURTH 0x000000FF

/*
 *
 * convert the value to unsigned char array[4]
 * write onto game->arena starting at pos
 *
 */
void	place_value(t_game *game, int value, int pos)
{
	int				index;
	unsigned char	answer[4];

	index = 0;
	answer[0] = (value & FIRST) >> 24;
	answer[1] = (value & SECOND) >> 16;
	answer[2] = (value & THIRD) >> 8;
	answer[3] = value & FOURTH;
	while (index < 4)
	{
		game->arena[pos] = answer[index];
		pos = (pos + 1) % MEM_SIZE;
		index++;
	}
}

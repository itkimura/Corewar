/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:36:42 by thle              #+#    #+#             */
/*   Updated: 2023/01/13 14:57:35 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * "aff" means  takes a value from a registry that was passed as a single
 * argument. Converts it to type char. And displays as an ASCII character.
 */
bool op_aff(t_game *game, t_carriage *carriage)
{
	if (game->flags_value[FLAG_A] != INITIAL_VALUE)
			ft_printf("%c\n", (char)carriage->registry[carriage->arg_value[0] - 1]);
	return (true);
}

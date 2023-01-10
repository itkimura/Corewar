/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:35:30 by thle              #+#    #+#             */
/*   Updated: 2023/01/10 13:46:27 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
This statement writes the value of the registry passed as the first parameter 
to the address:
current position + (<SECOND_ARGUMENT_VALUE> + <THIRD_ARGUMENT_VALUE>) % IDX_MOD.
*/
bool	op_sti(t_game *game, t_carriage *carriage)
{
	int value;
	int pos;
	
	value = get_value(game, carriage, FIRST_ARG, true);
	pos = carriage->pc + 
			((get_value(game, carriage, SECOND_ARG, true) + get_value(game, carriage, THIRD_ARG, true)) % IDX_MOD);
	place_value(game, value, pos);
	return true;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:31:59 by thle              #+#    #+#             */
/*   Updated: 2022/12/28 17:48:19 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

bool op_ld(t_game *game, t_carriage *carriage)
{
	if (get_arg_type(carriage, game->arena[carriage->pc] - 1, game->arena[carriage->pc + 1]) == false)
		return (false);
		for (int index = 0; index < 4; index++)
		ft_printf("carriage->arg[%d] = %d\n", index, carriage->arg[index]);
	collect_arg_values(carriage, game->arena);
	for (int index = 0; index < 4; index++)
		ft_printf("carriage->arg_value[%d] = %d\n", index, carriage->arg_value[index]);
	return false;
}

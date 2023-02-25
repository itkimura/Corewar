/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2023/02/25 13:12:25 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

bool	is_number(char *argv)
{
	int		index;
	long	nb;

	index = 0;
	while (argv[index])
	{
		if (!(argv[index] == '+' && index == 0)
			&& !(argv[index] >= '0' && argv[index] <= '9'))
			return (false);
		index++;
	}
	if (index > 10)
		return (false);
	nb = ft_atoli(&argv[index]);
	if (nb > INT_MAX && nb >= 0)
		return (false);
	return (true);
}

/*
 *  if the current argv is after flag_n or not
 */
bool	is_after_flag_n(t_game *game)
{
	if (game->flags_value[FLAG_N] != INITIAL_VALUE)
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/07 15:00:15 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* validate nb and return true or false*/
t_bool validate_n_flag_nb(char *argv, int index, t_flag *flag)
{
	int nb = ft_atoi(argv[index]);
	*flag = FLAG_N;
	if (nb > MAX_PLAYERS)
		return (FLASE);
	// need to check if the player n used or now
	if (game->player_array[nb]->fix_position == true)
		return (false);
	return (true);
}
/*
return which flag by ft_strcmp
*/
t_bool which_flag(char *argv, int index, t_flag *flag)
{
	// if (ft_strcmp(arv, "-d") == 0)
	// 	return (FLAG_DUMP);
	if (ft_strcmp(arv, "-n") == 0)
		return (validate_n_flag_nb(argv, ++index, flag));
	return (TRUE);
}

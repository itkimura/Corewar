/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 10:43:36 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

t_bool is_number(char *argv)
{
	int	index;

	index = 0;
	while (argv[index])
	{
		if (!(argv[index] >= '0' && argv[index] <= '9'))
			return (FALSE);
		index++;
	}
	return (TRUE);
}

/* 
 * validate nb and return true or false
 */
t_bool validate_n_flag_nb(char *argv, t_vm_flag *flag, t_game *game)
{
	int nb;

	if (is_number(argv) == FALSE)
		return (print_error("-n flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_N;
	if (nb > MAX_PLAYERS)
		return (print_error("-n flag", WRONG_NB));
	// need to check if the player n used or now
	if (game->player_array[nb]->fix_position == TRUE)
		return (TRUE);
	return (TRUE);
}

/* 
 * validate nb and return true or false
 */
t_bool validate_d_flag_nb(char *argv, t_vm_flag *flag, t_game *game)
{
	int nb;
}
/*
return which flag by ft_strcmp
*/
t_bool which_flag(char **argv, int index, t_vm_flag *flag, t_game *game)
{
	if (ft_strcmp(argv[index], "-d") == 0)
		return (TRUE);
	if (ft_strcmp(argv[index], "-n") == 0)
		return (validate_n_flag_nb(argv[++index], flag, game));
	return (TRUE);
}

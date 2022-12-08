/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 16:13:33 by itkimura         ###   ########.fr       */
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
 *  if the current argv is after flag_n or not
 */
t_bool is_after_flag_n(t_game *game)
{
	if (game->flags_value[FLAG_N])
		return (TRUE);
	return (FALSE);
}

/* 
 * validate nb and return true or false
 */
t_bool validate_n_flag_nb(char *argv, t_vm_flag *flag, t_game *game)
{
	int nb;

	if (is_after_flag_n(game) == TRUE)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == FALSE)
		return (print_error("-n flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_N;
	if (nb > MAX_PLAYERS)
		return (print_error("-n flag", WRONG_NB));
	// need to check if the player n used or now
	if (game->player_array[nb] && game->player_array[nb]->fix_position == TRUE)
		return (print_error("-n flag", WRONG_NB));
	game->flags_value[FLAG_N] = nb;
	return (TRUE);
}


/* 
 * validate nb and return true or false
 */
t_bool validate_d_flag_nb(char *argv, t_vm_flag *flag, t_game *game)
{
	int nb;

	if (is_after_flag_n(game) == TRUE)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == FALSE)
		return (print_error("-d flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_DUMP;
	game->flags_value[FLAG_DUMP] = nb;
	return (TRUE);
}

/*
return which flag by ft_strcmp
*/
t_bool which_flag(char **argv, int *index, t_vm_flag *flag, t_game *game)
{
	if (ft_strcmp(argv[*index], "-d") == 0)
		return (validate_d_flag_nb(argv[++(*index)], flag, game));
	if (ft_strcmp(argv[*index], "-n") == 0)
		return (validate_n_flag_nb(argv[++(*index)], flag, game));
	return (TRUE);
}
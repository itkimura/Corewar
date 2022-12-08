/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 17:07:38 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

bool is_number(char *argv)
{
	int index;

	index = 0;
	while (argv[index])
	{
		if (!(argv[index] >= '0' && argv[index] <= '9'))
			return (false);
		index++;
	}
	return (true);
}

/*
 *  if the current argv is after flag_n or not
 */
bool is_after_flag_n(t_game *game)
{
	if (game->flags_value[FLAG_N])
		return (true);
	return (false);
}

/*
 * validate nb and return true or false
 */
bool validate_n_flag_nb(char *argv, t_vm_flag *flag, t_game *game)
{
	int nb;

	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == false)
		return (print_error("-n flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_N;
	if (nb > MAX_PLAYERS)
		return (print_error("-n flag", WRONG_NB));
	// need to check if the player n used or now
	if (game->player_array[nb] && game->player_array[nb]->fix_position == true)
		return (print_error("-n flag", WRONG_NB));
	game->flags_value[FLAG_N] = nb;
	return (true);
}

/*
 * validate nb and return true or false
 */
bool validate_d_flag_nb(char *argv, t_vm_flag *flag, t_game *game)
{
	int nb;

	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == false)
		return (print_error("-d flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_DUMP;
	game->flags_value[FLAG_DUMP] = nb;
	return (true);
}

/*
return which flag by ft_strcmp
*/
bool which_flag(char **argv, int *index, t_vm_flag *flag, t_game *game)
{
	if (ft_strcmp(argv[*index], "-d") == 0)
		return (validate_d_flag_nb(argv[++(*index)], flag, game));
	if (ft_strcmp(argv[*index], "-n") == 0)
		return (validate_n_flag_nb(argv[++(*index)], flag, game));
	return (true);
}

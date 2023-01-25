/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/24 21:00:42 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * validate "-n" nb and return true or false
 */
bool	validate_n_flag(char *argv, t_vm_flag *flag, t_game *game)
{
	int	nb;

	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == false)
		return (print_error("-n flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_N;
	if (nb > MAX_PLAYERS || nb <= 0)
		return (print_error("-n flag", WRONG_NB));
	if (game->players_in_order[nb - 1] != NULL)
		return (print_error("-n flag", WRONG_NB));
	game->flags_value[FLAG_N] = nb;
	return (true);
}

/*
 * validate "-d" and nb and return true or false
 */
bool	validate_d_flag(char *argv, t_vm_flag *flag, t_game *game)
{
	int	nb;

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
 * validate -s flag and save number in game->flag_value;
 */
bool	validate_l_flag(char *argv, t_vm_flag *flag, t_game *game)
{
	int	nb;

	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == false)
		return (print_error("-l flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_L;
	game->flags_value[FLAG_L] = nb;
	return (true);
}

/*
 * validate "-a" flag
 */
bool	validate_a_flag(t_vm_flag *flag, t_game *game)
{
	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	*flag = FLAG_A;
	game->flags_value[FLAG_A] = 1;
	return (true);
}

/*
 * validate "-s" flag
 */
bool	validate_s_flag(char *argv, t_vm_flag *flag, t_game *game)
{
	int	nb;

	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (is_number(argv) == false)
		return (print_error("-s flag", WRONG_NB));
	nb = ft_atoi(argv);
	*flag = FLAG_S;
	game->flags_value[FLAG_S] = nb;
	return (true);
}

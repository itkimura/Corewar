/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2023/02/25 14:58:20 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

static bool	validate_v_nb(int nb)
{
	if (nb == FO_ESSENTIALS
		|| nb == FO_LIVES
		|| nb == FO_CYCLES
		|| nb == FO_OPERAIONS
		|| nb == FO_DEATHS
		|| nb == FO_ADV)
		return (true);
	return (false);
}

/* 
 * validate -s flag and save number in game->flag_value;
 */
bool	validate_v_flag(char *argv, t_vm_flag *flag, t_game *game)
{
	int	nb;

	if (is_after_flag_n(game) == true)
		return (print_error("", NO_PLAYER_AFTER_FLAG_N));
	if (argv == NULL)
		return (print_help(), false);
	if (is_number(argv) == false)
		return (print_error("-v flag", WRONG_NB));
	nb = ft_atoi(argv);
	if (validate_v_nb(nb) == false)
		return (print_error("-v flag", WRONG_NB));
	*flag = FLAG_V;
	game->flags_value[FLAG_V] = nb;
	return (true);
}

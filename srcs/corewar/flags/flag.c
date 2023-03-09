/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:57 by itkimura          #+#    #+#             */
/*   Updated: 2023/02/25 13:15:55 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * return which flag by ft_strcmp
 */
bool	which_flag(char **argv, int *index, t_vm_flag *flag, t_game *game)
{
	*flag = NOT_FLAG;
	if (ft_strcmp(argv[*index], "-dump") == 0
		|| ft_strcmp(argv[*index], "-d") == 0)
		return (validate_d_flag(argv[++(*index)], flag, game));
	if (ft_strcmp(argv[*index], "-n") == 0)
		return (validate_n_flag(argv[++(*index)], flag, game));
	if (ft_strcmp(argv[*index], "-v") == 0)
		return (validate_v_flag(argv[++(*index)], flag, game));
	if (ft_strcmp(argv[*index], "-a") == 0)
		return (validate_a_flag(flag, game));
	if (ft_strcmp(argv[*index], "-s") == 0)
		return (validate_s_flag(argv[++(*index)], flag, game));
	if (ft_strcmp(argv[*index], "--lld-size-2") == 0)
		return (validate_lld_flag(flag, game));
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:21 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 17:34:45 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

/* like atoi, convert bytes to decimal */
uint32_t	bytes_to_decimal(unsigned char *bytes, int start_idx, int end_idx)
{
	uint32_t	res;
	uint32_t	tmp;
	short int	shifted_value;

	shifted_value = 0;
	res = 0;
	while (end_idx >= start_idx)
	{
		tmp = (uint32_t)bytes[end_idx];
		res = (tmp << shifted_value) | res;
		shifted_value += 8;
		end_idx--;
	}
	return (res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:21 by thle              #+#    #+#             */
/*   Updated: 2022/12/28 14:09:26 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

/*
 * reverse_bytes
 *
 * read the bytes depending on T_DIR siz, 2 or 4
 * short -> 2 bytes
 * int -> 4 bytes
 */
int reverse_bytes(unsigned char *bytes, unsigned int pos, int nbytes)
{
	unsigned char	number[4];
	int				index;

	index = 0;
	while (index < 4)
	{
		if ((nbytes == 2 && index > 1) || (nbytes == 1 && index > 0))
			number[index] = '\0';
		else
			number[index] = bytes[pos + (nbytes - (index + 1))];
		index++;
	}
	return (*(int *)&number[0]);
}

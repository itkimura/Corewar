/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:21 by thle              #+#    #+#             */
/*   Updated: 2023/01/13 17:16:23 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
 * char_to_int
 *
 * read the bytes depending on T_DIR siz, 2 or 4
 * short -> 2 bytes
 * int -> 4 bytes
 */
int	char_to_int(unsigned char *bytes, unsigned int pos, int nbytes, bool is_arena)
{
	unsigned char	number[4];
	int				index;

	index = 0;
	while (index < 4)
	{
		if (nbytes == 2 && index > 1)
			number[index] = '\0';
		else
		{
			if (is_arena == true)
				number[index] = bytes[(pos + (nbytes - (index + 1))) % MEM_SIZE];
			else
				number[index] = bytes[pos + (nbytes - (index + 1))];
		}
		index++;
	}
	if (nbytes == 4)
		return (*(int *)&number[0]);
	return (*(short *)&number[0]);
}

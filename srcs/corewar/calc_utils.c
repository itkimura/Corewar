/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:34:21 by thle              #+#    #+#             */
/*   Updated: 2023/01/05 13:12:24 by thle             ###   ########.fr       */
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
int char_to_int(unsigned char *bytes, unsigned int pos, int nbytes)
{
	unsigned char number[4];
	int index;

	index = 0;
	while (index < 4)
	{
		if (nbytes == 2 && index > 1)
			number[index] = '\0';
		else
			number[index] = bytes[pos + (nbytes - (index + 1))];
		index++;
	}
	if (nbytes == 4)
		return (*(int *)&number[0]);
	return (*(short *)&number[0]);
}


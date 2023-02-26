/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:31:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/26 12:19:33 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_size(char *str, int code)
{
	int	len;

	len = ft_strlen(str);
	if (code == 1)
		if (len >= PROG_NAME_LENGTH)
			return (1);
	if (code == 2)
		if (len >= COMMENT_LENGTH)
			return (1);
	return (0);
}

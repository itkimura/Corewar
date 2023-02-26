/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:31:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/26 11:17:37 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_size(char *str, int code)
{
	int	len;

	len = ft_strlen(str);
	ft_printf("str == %s strlen == %d\n", str, len);
	if (code == 1)
		if (len >= PROG_NAME_LENGTH)
			return (1);
	if (code == 2)
		if (len >= COMMENT_LENGTH)
			return (1);
	return (0);
}

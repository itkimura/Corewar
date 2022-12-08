/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:23:23 by leotran           #+#    #+#             */
/*   Updated: 2022/10/05 23:14:53 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	i;
	long	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign = 1 - (2 * (nptr[i++] == '-'));
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i++] - '0');
		if (nptr[i] != '\0' && (nptr[i] == ' ' || !ft_isdigit(nptr[i])))
			return (0);
	}
	return (res * sign);
}

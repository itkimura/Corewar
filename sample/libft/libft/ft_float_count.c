/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:58:23 by leotran           #+#    #+#             */
/*   Updated: 2022/02/28 13:12:08 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_fractionalnum_count(int precision, int precision_flag)
{
	size_t	count;

	count = (size_t)precision + 1;
	if (precision == 0 && precision_flag == 1)
		count = 0;
	else if (precision_flag == 0)
		count = 7;
	return (count);
}

size_t	ft_float_count(long double num, int precision, int precision_flag)
{
	size_t		count;
	long double	sign;

	count = (num < 0);
	sign = 1 - 2 * (num < 0);
	num *= sign;
	count += get_fractionalnum_count(precision, precision_flag);
	count += ft_int_base_count((long long)num, 10);
	return (count);
}

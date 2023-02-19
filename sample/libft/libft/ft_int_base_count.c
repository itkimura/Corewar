/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_base_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:58:23 by leotran           #+#    #+#             */
/*   Updated: 2022/03/06 13:59:39 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_int_base_count(long long num, int base)
{
	int	count;

	count = 0;
	if (num <= 0)
	{
		num *= -1;
		count++;
	}	
	while (num > 0)
	{
		num /= (long long)base;
		count++;
	}
	return (count);
}

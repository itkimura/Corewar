/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_u_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:54:57 by leotran           #+#    #+#             */
/*   Updated: 2022/02/12 14:09:53 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_u_nbr(unsigned long long n)
{
	unsigned long long	i;
	int					count;

	i = 1;
	count = 0;
	while (i <= (n / 10))
	{
		i *= 10;
		count++;
	}
	while (count > 0)
	{
		ft_putchar((n / i) + '0');
		n %= i;
		i /= 10;
		count--;
	}
	ft_putchar(n + '0');
}

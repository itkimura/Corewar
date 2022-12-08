/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 02:22:44 by leo               #+#    #+#             */
/*   Updated: 2022/02/12 16:42:55 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddr(void *arr)
{
	ft_putstr("0x");
	ft_putstr(ft_uitoa_base((unsigned long long)arr, 16, 0));
}

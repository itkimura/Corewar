/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:48:13 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 15:09:51 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* hash * 33 + c */
unsigned long	hash(char *str)
{
	unsigned long	hash;
	unsigned long	i;

	hash = 5381;
	i = 0;
	while (str[i])
		hash = ((hash << 5) + hash) + str[i++];
	return (hash % HASHTABLESIZE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 03:12:42 by leo               #+#    #+#             */
/*   Updated: 2022/09/23 11:41:20 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "ft_printf.h"

void	ft_nodeprint(t_node **head)
{
	t_node	*current;

	current = *head;
	while (current)
	{
		ft_printf("%d ", current->num);
		current = current->next;
	}
	ft_printf("\n");
}

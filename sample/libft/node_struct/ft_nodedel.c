/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodedel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:40:58 by leotran           #+#    #+#             */
/*   Updated: 2022/03/21 15:19:02 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	ft_nodedel(t_node **head)
{
	t_node	*current;
	t_node	*next_node;

	current = (*head);
	while (current)
	{
		next_node = current->next;
		free(current);
		current = NULL;
		current = next_node;
	}
	(*head) = NULL;
}

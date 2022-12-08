/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeadd_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:24:25 by leotran           #+#    #+#             */
/*   Updated: 2022/09/23 10:44:49 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	ft_nodeadd_end(t_node **tail, t_node *node)
{
	(*tail)->next = node;
	node->prev = (*tail);
	node->next = NULL;
	(*tail) = node;
}

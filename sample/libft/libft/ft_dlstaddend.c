/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:10:56 by leotran           #+#    #+#             */
/*   Updated: 2022/03/17 19:15:47 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstaddend(t_dlist **alst, t_dlist *new)
{
	t_dlist	*temp;

	temp = (*alst);
	if (alst == NULL || new == NULL)
		return ;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->previous = temp;
	new->next = NULL;
}

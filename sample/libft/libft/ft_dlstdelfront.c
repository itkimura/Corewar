/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:40:52 by leotran           #+#    #+#             */
/*   Updated: 2022/03/17 19:20:49 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelfront(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist	*list;

	list = (*alst);
	(*del)(list->content, list->content_size);
	(*alst) = list->next;
	(*alst)->previous = NULL;
	if (list != NULL)
	{
		free(list);
		list = NULL;
	}
}

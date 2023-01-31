/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:04:53 by leotran           #+#    #+#             */
/*   Updated: 2022/03/17 19:20:15 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	list = (*alst);
	(*del)(list->content, list->content_size);
	(*alst) = list->next;
	if (list != NULL)
	{
		free(list);
		list = NULL;
	}
}

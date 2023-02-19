/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:02:37 by leotran           #+#    #+#             */
/*   Updated: 2022/03/17 19:14:43 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstaddfront(t_dlist **alst, t_dlist *new)
{
	new->next = (*alst);
	(*alst)->previous = new;
	(*alst) = new;
	(*alst)->previous = NULL;
}

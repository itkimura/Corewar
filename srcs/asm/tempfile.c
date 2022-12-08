/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:58:36 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 11:57:50 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_hashtable(t_asmdata *data)
{
	for (int i = 0; i < HASHTABLESIZE; i++) {
		t_hashstatement	*tmp = data->hashtable[i];
		while (tmp) {
			ft_printf("Name: {%s}\n", tmp->name);
			tmp = tmp->next;
		}
	}
}
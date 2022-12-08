/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tempfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:58:36 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 12:26:18 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_statement(t_statement statement)
{
	ft_printf("code: [%d] ", statement.code);
	ft_printf("name: {%s} ", statement.name);
	if (statement.argcode == true)
		ft_printf("argcode: {%s} ", "true");
	else
		ft_printf("argcode: {%s} ", "false");
	ft_printf("args: [%d]\n", statement.args);
}

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

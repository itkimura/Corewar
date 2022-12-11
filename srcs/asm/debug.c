/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:58:36 by leo               #+#    #+#             */
/*   Updated: 2022/12/11 12:20:11 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_statement(t_asmdata *data, char *name)
{
	t_statement	statement;
	int			index;

	index = get_statement_index(data, name);
	if (index == -1)
		exit(1);
	statement = g_statements[index];
	ft_printf("[Statement code]: {%d} ", statement.code);
	ft_printf("[Name]: {%s} ", statement.name);
	if (statement.argcode == true)
		ft_printf("[Argcode]: {%s} ", "true");
	else
		ft_printf("[Argcode]: {%s} ", "false");
	ft_printf("[Args]: {%d}\n", statement.args);
}

void	print_hashtable(t_asmdata *data)
{
	for (int i = 0; i < HASHTABLESIZE; i++) {
		t_hashstatement	*tmp = data->hashtable[i];
		ft_printf("{%p}:\n", tmp);
		while (tmp) {
			ft_printf("	Name: {%s}\n", tmp->name);
			tmp = tmp->next;
		}
	}
}

void	print_hashlabel(t_asmdata *data)
{
	for (int i = 0; i < HASHTABLESIZE; i++) {
		t_labels	*tmp = data->labels[i];
		ft_printf("{%p}:\n", tmp);
		while (tmp) {
			ft_printf("i:[%d] Name: {%s} ptr {%s}\n", i, tmp->name, tmp->ptr);
			tmp = tmp->next;
		}
	}
}

void	print_oplist(t_asmdata *data)
{
	for (t_op **tmp = data->oplist; *tmp; tmp++) {
		ft_printf("%s\n", (*tmp)->instruction);
	}
}

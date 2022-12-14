/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:58:36 by leo               #+#    #+#             */
/*   Updated: 2022/12/14 20:19:10 by leo              ###   ########.fr       */
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
	t_hashstatement	*tmp;
	int				i;

	i = 0;
	while (i < HASHTABLESIZE)
	{
		tmp = data->hashtable[i];
		ft_printf("{%p}:\n", tmp);
		while (tmp)
		{
			ft_printf("	Name: {%s}\n", tmp->name);
			tmp = tmp->next;
		}
		i++;
	}
}

void	print_hashlabel(t_asmdata *data)
{
	t_labels	*tmp;
	t_op		*result;
	int			i;

	i = 0;
	while (i < HASHTABLESIZE)
	{
		tmp = data->labels[i];
		ft_printf("{%p}:\n", tmp);
		while (tmp)
		{
			ft_printf("i:[%d] label: {%s}", i, tmp->name);
			if (!tmp->ptr->statement)
			{
				ft_printf("ptr to label: {%s}", tmp->ptr->label);
				get_label_adr(data, &result, tmp->ptr->label);
				ft_printf(" final statment: {%s}\n", result->statement);
			}	
			else
				ft_printf("ptr to statement: {%s}\n", tmp->ptr->statement);
			tmp = tmp->next;
		}
		i++;
	}
}

void	print_oplist(t_asmdata *data)
{
	t_op	**tmp;
	int		i;

	tmp = data->oplist;
	while (*tmp)
	{
		i = 0;
		if ((*tmp)->statement)
		{
			ft_printf("statement: {%s} byte: [%d] totbyte: [%d]\n", \
			(*tmp)->statement, (*tmp)->byte, (*tmp)->totalbyte);
			while (i < 3)
			{
				if ((*tmp)->arg[i])
					ft_printf("	arg: {%s}\n", (*tmp)->arg[i]);
				i++;
			}
			ft_printf("\n");
		}
		else
			ft_printf("label: {%s}\n", (*tmp)->label);
		tmp++;
	}
}

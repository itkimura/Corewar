/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:09:08 by leo               #+#    #+#             */
/*   Updated: 2023/02/26 21:40:31 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	init_statement(t_hashstatement **statement, int i)
{
	t_hashstatement	*tmp;

	tmp = (t_hashstatement *)malloc(sizeof(t_hashstatement));
	if (!tmp)
		return (0);
	tmp->name = ft_strdup(g_statements[i].name);
	if (!tmp->name)
		return (0);
	tmp->index = g_statements[i].code - 1;
	tmp->next = NULL;
	if (*statement)
		tmp->next = *statement;
	*statement = tmp;
	return (1);
}

static int	insert_statements(t_asmdata *data)
{
	int				i;
	int				index;

	i = 0;
	index = -1;
	while (i < HASHTABLESIZE)
	{
		index = hash(g_statements[i].name);
		if (!init_statement(&data->hashtable[index], i))
			return (0);
		i++;
	}
	return (1);
}

int	validate_statement(t_asmdata *data, char *ptr, int index, int *i)
{
	char	*statement;
	int		j;

	statement = NULL;
	j = *i;
	while (ptr[j] && ft_isalpha(ptr[j]))
		j++;
	if (ptr[j] == ' ' || ptr[j] == '\t' || ptr[j] == DIRECT_CHAR)
		statement = ft_strsub(ptr, *i, j - (*i));
	if (!statement || get_statement_index(data, statement) == -1)
	{
		ft_strdel(&statement);
		return (0);
	}
	data->oplist[index]->statement = statement;
	*i = j;
	while (ptr[j] && ptr[j] != COMMENT_CHAR && ptr[j] != ALTERNATE_COMMENT_CHAR)
		j++;
	while (ptr[j])
		ptr[j++] = '#';
	return (1);
}

int	get_statement_index(t_asmdata *data, char *name)
{
	t_hashstatement	*tmp;

	tmp = data->hashtable[hash(name)];
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp->index);
		tmp = tmp->next;
	}
	return (-1);
}

int	init_statements_table(t_asmdata *data)
{
	int	i;

	i = 0;
	data->hashtable = (t_hashstatement **)malloc(\
		sizeof(t_hashstatement *) * HASHTABLESIZE);
	if (!data->hashtable)
		return (0);
	while (i < HASHTABLESIZE)
		data->hashtable[i++] = NULL;
	return (insert_statements(data));
}

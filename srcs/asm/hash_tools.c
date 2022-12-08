/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:48:13 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 15:08:00 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	init_statements(t_hashstatement **statement, int i)
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
		if (!init_statements(&data->hashtable[index], i))
			return (0);
		i++;
	}
	return (1);
}

/* hash * 33 + c */
unsigned long	hash(char *str)
{
	unsigned long	hash;
	unsigned long	i;

	hash = 5381;
	i = 0;
	while (str[i])
		hash = ((hash << 5) + hash) + str[i++];
	return (hash % HASHTABLESIZE);
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

int	init_hashtable(t_asmdata *data)
{
	int	i;

	i = 0;
	data->hashtable = (t_hashstatement **)malloc(\
		sizeof(t_hashstatement *) * HASHTABLESIZE);
	if (!data->hashtable)
		return (0);
	while (data->hashtable[i])
		data->hashtable[i++] = NULL;
	return (insert_statements(data));
}

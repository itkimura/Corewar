/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:55 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 15:14:28 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	int	init_label(t_labels **label, char *name, int index)
{
	t_labels	*tmp;

	tmp = (t_labels *)malloc(sizeof(t_labels));
	if (!tmp)
		return (0);
	tmp->name = ft_strdup(name);
	if (!tmp->name)
		return (0);
	tmp->index = index;
	if (*label)
		tmp->next = *label;
	*label = tmp;
	return (1);
}

void	insert_label(t_asmdata *data, char *name, int index)
{
	int	hashindex;

	hashindex = hash(name);
	if (!init_label(&data->labels[hashindex], name, index))
		free_exit(data);
}

int	get_label_index(t_asmdata *data, char *name)
{
	t_labels	*tmp;

	tmp = data->labels[hash(name)];
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return (tmp->index);
		tmp = tmp->next;
	}
	return (-1);
}

int	init_labels_table(t_asmdata *data)
{
	int	i;

	i = 0;
	data->labels = (t_labels **)malloc(\
		sizeof(t_labels *) * HASHTABLESIZE);
	if (!data->labels)
		return (0);
	while (i < HASHTABLESIZE)
		data->labels[i++] = NULL;
	return (1);
}

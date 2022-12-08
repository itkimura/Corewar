/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:55 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 14:42:05 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	int	init_label(t_labels **label, char *name, int index)
{
	*label = (t_labels *)malloc(sizeof(t_labels));
	if (!(*label))
		return (0);
	(*label)->name = ft_strdup(name);
	if (!(*label)->name)
		return (0);
	(*label)->index = index;
	return (1);
}

void	get_label_index(t_asmdata *data, char *label)
{
	/* get the instruction index of label */
	if (data || label)
		return ;
}

void	insert_label(t_asmdata *data, char *name, int index)
{
	int			hashindex;

	hashindex = hash(name);
	if (!init_label(&data->labels[hashindex], name, index))
		free_exit(data);
}

int	init_labels(t_asmdata *data)
{
	int	i;

	i = 0;
	data->labels = (t_labels **)malloc(sizeof(t_labels *) * HASHTABLESIZE);
	if (data->labels)
		return (0);
	while (i < HASHTABLESIZE)
		data->labels[i++] = NULL;
	return (1);
}

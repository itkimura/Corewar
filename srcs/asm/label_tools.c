/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:55 by leo               #+#    #+#             */
/*   Updated: 2022/12/14 18:37:00 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	int	init_label(t_labels **label, t_op *ptr, char *name)
{
	t_labels	*tmp;

	tmp = (t_labels *)malloc(sizeof(t_labels));
	if (!tmp)
		return (0);
	tmp->name = name;
	tmp->ptr = ptr;
	if (*label)
		tmp->next = *label;
	*label = tmp;
	return (1);
}

void	insert_label(t_asmdata *data, t_op *ptr, char *name)
{
	int	hashindex;

	hashindex = hash(name);
	if (!init_label(&data->labels[hashindex], ptr, name))
		free_exit(data, MALLOCFAIL, ERROR);
}

int	get_label_adr(t_asmdata *data, t_op **ptr, char *name)
{
	t_labels	*tmp;

	if (!name)
		return (0);
	tmp = data->labels[hash(name)];
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
		{
			if (tmp->ptr->label && !tmp->ptr->statement)
				get_label_adr(data, ptr, tmp->ptr->label);
			else
				*ptr = tmp->ptr;
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
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

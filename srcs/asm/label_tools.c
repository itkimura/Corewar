/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:55 by leo               #+#    #+#             */
/*   Updated: 2022/12/09 10:20:26 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	int	init_label(t_labels **label, char *name, char *ptr)
{
	t_labels	*tmp;

	tmp = (t_labels *)malloc(sizeof(t_labels));
	if (!tmp)
		return (0);
	tmp->name = ft_strdup(name);
	if (!tmp->name)
		return (0);
	tmp->ptr = &ptr;
	if (*label)
		tmp->next = *label;
	*label = tmp;
	return (1);
}

void	insert_label(t_asmdata *data, char *name, char *ptr)
{
	int	hashindex;

	hashindex = hash(name);
	if (!init_label(&data->labels[hashindex], name, ptr))
		free_exit(data);
}

char	*get_label_adr(t_asmdata *data, char *name)
{
	t_labels	*tmp;

	tmp = data->labels[hash(name)];
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return (*tmp->ptr);
		tmp = tmp->next;
	}
	return (NULL);
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

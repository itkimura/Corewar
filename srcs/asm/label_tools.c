/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:55 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 14:21:58 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_label_index(t_asmdata *data, char *label)
{
	/* get the instruction index of label */
}

void	insert_label(t_asmdata *data, char *label)
{
	/* insert label to hashtable of labels */
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

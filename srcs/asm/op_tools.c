/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 03:39:40 by leo               #+#    #+#             */
/*   Updated: 2022/12/16 13:07:26 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	init_op(t_op **op, char *line)
{
	*op = (t_op *)malloc(sizeof(t_op));
	if (!(*op))
		return (0);
	(*op)->instruction = line;
	(*op)->statement = NULL;
	(*op)->label = NULL;
	(*op)->arg[0] = NULL;
	(*op)->arg[1] = NULL;
	(*op)->arg[2] = NULL;
	(*op)->argcode = 0;
	(*op)->args = 0;
	(*op)->totalbyte = 0;
	(*op)->byte = 0;
	return (1);
}

int	resize_op_table(t_asmdata *data)
{
	t_op	**tmp;
	int		i;

	i = 0;
	data->opsize *= 2;
	if (!init_op_table(&tmp, data->opsize))
		free_exit(data, MALLOCFAIL, ERROR);
	while (data->oplist[i])
	{
		tmp[i] = data->oplist[i];
		i++;
	}
	free(data->oplist);
	data->oplist = tmp;
	return (1);
}

int	init_op_table(t_op	***oplist, int size)
{
	int	i;

	i = 0;
	*oplist = (t_op **)malloc(sizeof(t_op *) * size);
	if (!(*oplist))
		return (0);
	while (i < size)
		(*oplist)[i++] = NULL;
	return (1);
}

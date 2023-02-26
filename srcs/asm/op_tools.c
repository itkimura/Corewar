/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 03:39:40 by leo               #+#    #+#             */
/*   Updated: 2023/02/26 21:07:43 by leo              ###   ########.fr       */
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
	(*op)->arg_count = 0;
	(*op)->argcode = 0;
	(*op)->args = 0;
	(*op)->totalbyte = 0;
	(*op)->byte = 0;
	return (1);
}

int	resize_op_table(t_asmdata *data)
{
	t_op	**tmp;
	int		tmpsize;
	int		i;

	i = 0;
	tmpsize = data->opsize * 2;
	if (!init_op_table(&tmp, tmpsize))
		free_exit(data, MALLOCFAIL, ERROR);
	while (i < data->opsize)
	{
		tmp[i] = data->oplist[i];
		i++;
	}
	free(data->oplist);
	data->opsize = tmpsize;
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

void	add_byte_to_op(t_asmdata *data, int index, int arg_code, int tmp_index)
{
	t_op	*tmp;
	int		byte;

	tmp = data->oplist[index];
	byte = 0;
	if (!tmp->byte)
	{
		while (index > 0 && !data->oplist[index - 1]->statement)
			index--;
		if (index != 0)
			tmp->totalbyte = data->oplist[index - 1]->totalbyte;
		tmp->byte += 1 + (g_statements[tmp_index].argcode);
		tmp->totalbyte += tmp->byte;
	}
	if (arg_code == REG_CODE)
		byte = 1;
	else if (arg_code == IND_CODE)
		byte = 2;
	else if (arg_code == DIR_CODE)
		byte = g_statements[tmp_index].size;
	tmp->byte += byte;
	if (index == 0)
		tmp->totalbyte = tmp->byte;
	else
		tmp->totalbyte += byte;
}

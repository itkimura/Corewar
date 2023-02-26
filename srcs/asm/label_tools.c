/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:19:55 by leo               #+#    #+#             */
/*   Updated: 2023/02/26 11:51:26 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	init_label(t_labels **label, t_op *ptr, char *name)
{
	t_labels	*tmp;

	tmp = (t_labels *)malloc(sizeof(t_labels));
	if (!tmp)
		return (0);
	tmp->name = name;
	tmp->ptr = ptr;
	tmp->next = NULL;
	if (*label)
		tmp->next = *label;
	*label = tmp;
	return (1);
}

static void	insert_label(t_asmdata *data, t_op *ptr, char *name)
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

int	validate_label(t_asmdata *data, char *ptr, int index)
{
	char	*label;
	int		i;

	i = 0;
	while (ptr[i] && ft_strchr(LABEL_CHARS, ptr[i]))
		i++;
	if (ptr[i++] != LABEL_CHAR)
		return (0);
	label = ft_strsub(ptr, 0, i - 1);
	if (!label)
		free_exit(data, MALLOCFAIL, ERROR);
	data->oplist[index]->label = label;
	while (ptr[i] && (ptr[i] == ' ' || ptr[i] == '\t'))
		i++;
	if (ptr[i] && validate_statement(data, ptr, index, &i))
		validate_instruction(data, ptr, index, i);
	else if (ptr[i] && (ptr[i] != COMMENT_CHAR \
		&& ptr[i] != ALTERNATE_COMMENT_CHAR))
		free_exit(data, "Invalid instruction/label2", ERROR);
	insert_label(data, data->oplist[index + !(ptr[i])], label);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/13 03:05:14 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	validate_statement(t_asmdata *data, char *ptr, int i, int j)
{
	char	*statement;
	int		ret;

	statement = NULL;
	ret = 1;
	if (ptr[j] == ' ' || ptr[j] == '\t' || ptr[j] == DIRECT_CHAR \
		|| ptr[j] == LABEL_CHAR)
		statement = ft_strsub(ptr, i, j - i);
	if (!statement || get_statement_index(data, statement) == -1)
		ret = 0;
	ft_strdel(&statement);
	return (ret);
}

static int	validate_arguments(t_asmdata *data)
{
	if (!data)
		return (0);
	return (1);	
}

static void	seperate_instruction(t_asmdata *data, char *ptr)
{
	if (!data || !ptr)
		return ;
	validate_arguments(data);
}

static int	validate_label(t_asmdata *data, char *ptr, int index, int j)
{
	char	*label;

	while (ptr[j] && ft_strchr(LABEL_CHARS, ptr[j]))
		j++;
	if (ptr[j++] != LABEL_CHAR)
		return (0);
	label = ft_strsub(ptr, 0, j);
	if (!label)
		free_exit(data, MALLOCFAIL, ERROR);
	while (ptr[j] && (ptr[j] == ' ' || ptr[j] == '\t'))
		j++;
	if (ptr[j])
		ptr = &ptr[j];
	else
		ptr = data->oplist[index + 1]->instruction;
	insert_label(data, label, ptr);
	return (1);
}

void	parse_instructions(t_asmdata *data)
{
	char	*ptr;
	int		index;
	int		i;
	int		j;

	index = 0;
	while (index < data->opcount)
	{
		i = 0;
		j = 0;
		ptr = data->oplist[index]->instruction;
		while (ptr[i] == ' ' || ptr[i] == '\t')
			i++;
		j = i;
		while (ptr[j] && ft_isalpha(ptr[j]))
			j++;
		if (validate_statement(data, ptr, i, j))
			seperate_instruction(data, ptr);
		else if (i == 0 && !validate_label(data, ptr, index, j))
			free_exit(data, "Invalid instruction/label", ERROR);
		index++;
	}
}

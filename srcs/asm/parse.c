/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/11 23:07:46 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	validate_label(char *label)
{
	int	i;

	i = 0;
	while (label[i + 1])
	{
		if (!ft_strchr(LABEL_CHARS, label[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*seperate_label(t_asmdata *data, char *ptr, int i)
{
	char	*label;
	int		j;

	j = 0;
	while (ptr[j] && ptr[j] != LABEL_CHAR)
		j++;
	if (ptr[j - 1] == DIRECT_CHAR)
		return (ptr);
	label = ft_strsub(ptr, 0, ++j);
	if (!label)
		free_exit(data, MALLOCFAIL, ERROR);
	if (!validate_label(label))
		free_exit(data, "Invalid label", ERROR);
	while (ptr[j] && (ptr[j] == ' ' || ptr[j] == '\t'))
		j++;
	if (ptr[j])
		ptr = &ptr[j];
	else
		ptr = data->oplist[i + 1]->instruction;
	insert_label(data, label, ptr);
	ft_strdel(&label);
	return (ptr);
}

static int	seperate_instruction(t_asmdata *data, char *ptr)
{
	// ft_printf("instruction found: {%p}\n", &ptr);
	// ft_printf("	%s", ptr);
	if (!data || !ptr)
		return (0);
	return (1);
}

void	parse_instructions(t_asmdata *data)
{
	char	*ptr;
	int		i;

	i = 0;
	while (i < data->opcount)
	{
		ptr = data->oplist[i]->instruction;
		if (ft_strchr(ptr, LABEL_CHAR))
			ptr = seperate_label(data, ptr, i);
		else if (!seperate_instruction(data, ptr))
			free_exit(data, "Invalid instruction", ERROR);
		i++;
	}
}

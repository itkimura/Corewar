/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/14 18:38:13 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*seperate_arguments(char *arg, int start)
{
	int	end;

	if (arg[start] == '-' && ft_isdigit(arg[start + 1]))
		start++;
	else if (arg[start] == DIRECT_CHAR || arg[start] == LABEL_CHAR \
		|| arg[start] == 'r' || ft_isdigit(arg[start]))
	{
		end = start;
		while (arg[end] && arg[end] != ' ' && arg[end] != '\t' \
			&& arg[end] != COMMENT_CHAR && arg[end] != ALTERNATE_COMMENT_CHAR)
			end++;
		arg = ft_memmove((void *)&arg[0], (void *)&arg[start], end - start);
		arg[end - start] = '\0';
	}
	else
		return (NULL);
	return (arg);
}

static void	seperate_instruction(t_asmdata *data, char *ptr, int index, int i)
{
	char	**args;
	char	*tmp;
	int		j;
	int		start;

	tmp = &ptr[i];
	j = 0;
	args = ft_strsplit(tmp, SEPARATOR_CHAR);
	while (args && args[j])
	{
		start = 0;
		while (args[j][start] == ' ' || args[j][start] == '\t')
			start++;
		data->oplist[index]->arg[j] = seperate_arguments(args[j], start);
		j++;
	}
	if (!args)
		free_exit(data, "no arguements", ERROR);
	ft_memdel((void **)&args);
}

static int	validate_statement(t_asmdata *data, char *ptr, int index, int *i)
{
	char	*statement;
	int		j;

	statement = NULL;
	j = *i;
	while (ptr[j] && ft_isalpha(ptr[j]))
		j++;
	if (ptr[j] == ' ' || ptr[j] == '\t' || ptr[j] == DIRECT_CHAR \
		|| ptr[j] == LABEL_CHAR)
		statement = ft_strsub(ptr, *i, j - (*i));
	if (!statement || get_statement_index(data, statement) == -1)
	{
		ft_strdel(&statement);
		return (0);
	}
	data->oplist[index]->statement = statement;
	*i = j;
	return (1);
}

static int	validate_label(t_asmdata *data, char *ptr, int index)
{
	char	*label;
	int		i;

	i = 0;
	while (ptr[i] && ft_strchr(LABEL_CHARS, ptr[i]))
		i++;
	if (ptr[i++] != LABEL_CHAR)
		return (0);
	label = ft_strsub(ptr, 0, i);
	if (!label)
		free_exit(data, MALLOCFAIL, ERROR);
	data->oplist[index]->label = label;
	while (ptr[i] && (ptr[i] == ' ' || ptr[i] == '\t'))
		i++;
	if (ptr[i] && validate_statement(data, ptr, index, &i))
		seperate_instruction(data, ptr, index, i);
	else if (ptr[i] && (ptr[i] != COMMENT_CHAR \
		|| ptr[i] != ALTERNATE_COMMENT_CHAR))
		free_exit(data, "Invalid instruction/label2", ERROR);
	insert_label(data, data->oplist[index + !(ptr[i])], label);
	return (1);
}

void	parse_instructions(t_asmdata *data)
{
	char	*ptr;
	int		index;
	int		i;

	index = 0;
	while (index < data->opcount)
	{
		i = 0;
		ptr = data->oplist[index]->instruction;
		while (ptr[i] == ' ' || ptr[i] == '\t')
			i++;
		if (validate_statement(data, ptr, index, &i))
			seperate_instruction(data, ptr, index, i);
		else if (i == 0 && !validate_label(data, ptr, index))
			free_exit(data, "Invalid instruction/label", ERROR);
		index++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/14 10:17:22 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

static void	seperate_instruction(t_asmdata *data, char *ptr, int index, int j)
{
	char	**args;
	char	*tmp;
	int		i;
	int		start;

	tmp = &ptr[j];
	i = 0;
	args = ft_strsplit(tmp, SEPARATOR_CHAR);
	while (args && args[i])
	{
		start = 0;
		while (args[i][start] == ' ' || args[i][start] == '\t')
			start++;
		data->oplist[index]->arg[i] = seperate_arguments(args[i], start);
		i++;
	}
	if (!args)
		free_exit(data, "no arguements", ERROR);
	ft_memdel((void **)&args);
	//set byte and totalbyte = (index - 1)->totalbyte + byte. 
}

static int	validate_statement(t_asmdata *data, char *ptr, int index, int j)
{
	char	*statement;
	int		i;

	statement = NULL;
	i = 0;
	while (ptr[i] == ' ' || ptr[i] == '\t')
		i++;
	if (ptr[j] == ' ' || ptr[j] == '\t' || ptr[j] == DIRECT_CHAR \
		|| ptr[j] == LABEL_CHAR)
		statement = ft_strsub(ptr, i, j - i);
	if (!statement || get_statement_index(data, statement) == -1)
	{
		ft_strdel(&statement);
		return (0);
	}
	data->oplist[index]->statement = statement;
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
		if (validate_statement(data, ptr, index, j))
			seperate_instruction(data, ptr, index, j);
		else if (i == 0 && !validate_label(data, ptr, index, j))
			free_exit(data, "Invalid instruction/label", ERROR);
		index++;
	}
}

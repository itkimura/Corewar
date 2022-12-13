/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/13 14:21:44 by leo              ###   ########.fr       */
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

static int	seperate_arguments(t_asmdata *data, char **args, int index)
{
	char	*arg;
	int		i;
	int		start;
	int		end;

	i = 0;
	arg = NULL;
	while (args[i])
	{
		start = 0;
		end = 0;
		while (args[i][start] == ' ' || args[i][start] == '\t')
			start++;
		if (args[i][start] == '-' && ft_isdigit(args[i][start + 1]))
			start++;
		else if (args[i][start] == DIRECT_CHAR || args[i][start] == LABEL_CHAR \
			|| args[i][start] == 'r' || ft_isdigit(args[i][start]))
		{
			end = start;
			while (args[i][end] && args[i][end] != ' ' && args[i][end] != '\t' \
				&& args[i][end] != COMMENT_CHAR && args[i][end] != ALTERNATE_COMMENT_CHAR)
				end++;
			arg = ft_strsub(args[i], start, end - start);
			data->oplist[index]->arg[i] = arg;
		}
		else
			return (0);
		i++;
	}
	return (1);
}

static void	seperate_instruction(t_asmdata *data, char *ptr, int index, int j)
{
	char	**args;
	char	*tmp;

	tmp = &ptr[j];
	args = ft_strsplit(tmp, SEPARATOR_CHAR);
	if (!args || !seperate_arguments(data, args, index))
		free_exit(data, "invalid arguements", ERROR);
	//set byte and totalbyte = (index - 1)->totalbyte + byte. 
}

static int	validate_statement(t_asmdata *data, char *ptr, int index, int j)
{
	char	*statement;
	int		ret;
	int		i;

	statement = NULL;
	ret = 1;
	i = 0;
	while (ptr[i] == ' ' || ptr[i] == '\t')
		i++;
	if (ptr[j] == ' ' || ptr[j] == '\t' || ptr[j] == DIRECT_CHAR \
		|| ptr[j] == LABEL_CHAR)
		statement = ft_strsub(ptr, i, j - i);
	if (!statement || get_statement_index(data, statement) == -1)
		ret = 0;
	if (ret)
		data->oplist[index]->statement = statement;
	return (ret);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/15 01:34:26 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	validate_arg(char *arg)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	if (arg[0] == 'r' && ft_isdigit(arg[1]) \
		&& (!arg[2] || (ft_isdigit(arg[2]) && !arg[3])))
		res = REG_CODE;
	else if (arg[i] == DIRECT_CHAR)
	{
		res = DIR_CODE;
	}
	else if (arg[0] == LABEL_CHAR || arg[0] == '-' || ft_isdigit(arg[0]))
	{
		res = IND_CODE;
	}
	return (res);
}

static char	*trim_arg(t_asmdata *data, char *arg, int index, int start)
{
	int	bytecode;
	int	end;
	int	tmp_index;

	bytecode = 0;
	end = start;
	while (arg[end] && arg[end] != ' ' && arg[end] != '\t' \
		&& arg[end] != COMMENT_CHAR && arg[end] != ALTERNATE_COMMENT_CHAR)
		end++;
	arg = ft_memmove((void *)&arg[0], (void *)&arg[start], end - start);
	arg[end - start] = '\0';
	bytecode = validate_arg(arg);
	if (!bytecode)
		free_exit(data, "invalid arg", ERROR);
	tmp_index = get_statement_index(data, data->oplist[index]->statement);
	if (g_statements[tmp_index].argcode)
		data->oplist[index]->argcode = \
		data->oplist[index]->argcode << 2 ^ bytecode << 2;
	return (arg);
}

void	seperate_instruction(t_asmdata *data, char *ptr, int index, int i)
{
	char	**args;
	t_op	*op;
	int		j;
	int		start;

	j = 0;
	args = ft_strsplit(&ptr[i], SEPARATOR_CHAR);
	while (args && args[j])
	{
		start = 0;
		op = data->oplist[index];
		while (args[j][start] == ' ' || args[j][start] == '\t')
			start++;
		if (args[j][start] == '-' && ft_isdigit(args[j][start + 1]))
			start++;
		if (args[j][start] == DIRECT_CHAR || args[j][start] == LABEL_CHAR \
			|| args[j][start] == 'r' || ft_isdigit(args[j][start]))
			op->arg[j] = trim_arg(data, args[j], index, start);
		j++;
	}
	while (j++ < 3)
		op->argcode = op->argcode << 2;
	if (!args)
		free_exit(data, "ft_strsplit fail", ERROR);
	ft_memdel((void **)&args);
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

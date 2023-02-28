/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2023/03/01 01:03:12 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	validate_ind_arg(char *arg, int arg_code)
{
	int	tmp_code;
	int	i;

	tmp_code = arg_code;
	i = 1;
	if (arg[0] == LABEL_CHAR || arg[0] == '-' || ft_isdigit(arg[0]))
		tmp_code = IND_CODE;
	if (arg_code == DIR_CODE || arg[0] == '-')
		i++;
	if (arg[0] == LABEL_CHAR || arg_code)
	{
		while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
			i++;
	}
	else if (arg[0] != LABEL_CHAR)
	{
		while (arg[i] && ft_isdigit(arg[i]))
			i++;
	}
	if (arg[i] || (arg[0] == LABEL_CHAR && i == 1))
		tmp_code = 0;
	return (tmp_code);
}

static int	validate_arg(char *arg)
{
	int	arg_code;
	int	i;

	arg_code = 0;
	i = 1 + (arg[1] == '-');
	if (arg[0] == 'r' && arg[1] == '0' && arg[2] == '0')
		return (0);
	if (arg[0] == 'r' && ft_isdigit(arg[1]) \
		&& (!arg[2] || (ft_isdigit(arg[2]) && !arg[3])))
		return (REG_CODE);
	if (arg[0] == DIRECT_CHAR)
		arg_code = DIR_CODE;
	if (arg[0] == DIRECT_CHAR && arg[1] != LABEL_CHAR)
	{
		while (arg[i] == '0')
			i++;
		while (arg[i] && ft_isdigit(arg[i]))
			i++;
		if (arg[i] || i == 1 + (arg[1] == '-'))
			return (0);
	}
	else
		arg_code = validate_ind_arg(arg, arg_code);
	return (arg_code);
}

static char	*trim_arg(t_asmdata *data, char *arg, int index, int start)
{
	int	arg_code;
	int	end;
	int	tmp_index;

	arg_code = 0;
	end = start;
	while (arg[end] && !ft_isspace(arg[end]) \
		&& arg[end] != COMMENT_CHAR && arg[end] != ALTERNATE_COMMENT_CHAR)
		end++;
	if (!check_comment_after_arg(&arg[end]))
		return (NULL);
	arg = ft_memmove((void *)&arg[0], (void *)&arg[start], end - start);
	arg[end - start] = '\0';
	arg_code = validate_arg(arg);
	if (!arg_code)
		return (NULL);
	tmp_index = get_statement_index(data, data->oplist[index]->statement);
	if (g_statements[tmp_index].argcode)
		data->oplist[index]->argcode = \
		data->oplist[index]->argcode << 2 ^ arg_code << 2;
	data->oplist[index]->args = \
	data->oplist[index]->args << 3 | (1 << (arg_code -1));
	add_byte_to_op(data, index, arg_code, tmp_index);
	return (arg);
}

char	**seperate_instruction(t_asmdata *data, char *ptr, int index, int i)
{
	char	**args;
	int		j;
	int		start;

	j = 0;
	args = ft_strsplit(&ptr[i], SEPARATOR_CHAR);
	while (args && args[j])
	{
		start = 0;
		while (args[j][start] == ' ' || args[j][start] == '\t')
			start++;
		data->oplist[index]->arg[j] = trim_arg(data, args[j], index, start);
		if (!data->oplist[index]->arg[j] && free_args(args, j))
			ft_memdel((void **)&args);
		j++;
		data->oplist[index]->arg_count = j;
	}
	while (j++ < 3)
	{
		data->oplist[index]->argcode = data->oplist[index]->argcode << 2;
		data->oplist[index]->args = data->oplist[index]->args << 3;
	}
	if (!args)
		free_exit(data, "invalid args", ERROR);
	return (args);
}

void	parse_instructions(t_asmdata *data)
{
	char		*ptr;
	int			index;
	int			i;

	index = 0;
	while (index < data->opcount)
	{
		i = 0;
		ptr = data->oplist[index]->instruction;
		while (ptr[i] == ' ' || ptr[i] == '\t')
			i++;
		if (validate_statement(data, ptr, index, &i))
			check_instruction(data, ptr, index, i);
		else if (!validate_label(data, &ptr[i], index))
			free_exit(data, "Invalid instruction/label", ERROR);
		index++;
	}
}

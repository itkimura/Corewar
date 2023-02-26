/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2023/02/26 13:20:41 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	validate_ind_arg(char *arg, int res)
{
	int	tmp;
	int	i;

	tmp = res;
	i = 1;
	if (arg[0] == LABEL_CHAR || arg[0] == '-' || ft_isdigit(arg[0]))
		tmp = IND_CODE;
	if (res == DIR_CODE || arg[0] == '-')
		i++;
	if (arg[0] == LABEL_CHAR || res)
	{
		while (arg[i] && ft_strchr(LABEL_CHARS, arg[i]))
			i++;
	}
	else if (arg[0] != LABEL_CHAR)
	{
		while (arg[i] && ft_isdigit(arg[i]))
			i++;
	}
	if (arg[i])
		tmp = 0;
	return (tmp);
}

int	check_comment_after_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (!arg[i])
		return (1);
	if (arg[i] == COMMENT_CHAR || arg[i] == ALTERNATE_COMMENT_CHAR)
		return (1);
	return (0);
}

static int	validate_arg(char *arg)
{
	int	arg_code;
	int	i;

	arg_code = 0;
	i = 1;
	if (arg[0] == 'r' && arg[1] == '0' && arg[2] == '0')
		return (arg_code);
	if (arg[0] == 'r' && ft_isdigit(arg[1]) \
		&& (!arg[2] || (ft_isdigit(arg[2]) && !arg[3])))
		arg_code = REG_CODE;
	else if (arg[0] == DIRECT_CHAR)
		arg_code = DIR_CODE;
	if (arg[0] == DIRECT_CHAR && arg[1] != LABEL_CHAR)
	{
		while (arg[i] == '0')
			i++;
		while(arg[i] && ft_isdigit(arg[i]))
			i++;
		if (arg[i])
			arg_code = 0;
	}
	else if (arg[0] != 'r')
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
	if (!check_comment_after_arg(&arg[end]) || start + 1 == end)
		free_exit(data, "invalid arg (not a valid comment)", ERROR);
	arg = ft_memmove((void *)&arg[0], (void *)&arg[start], end - start);
	arg[end - start] = '\0';
	arg_code = validate_arg(arg);
	if (!arg_code)
		free_exit(data, "invalid arg", ERROR);
	tmp_index = get_statement_index(data, data->oplist[index]->statement);
	if (g_statements[tmp_index].argcode)
		data->oplist[index]->argcode = \
		data->oplist[index]->argcode << 2 ^ arg_code << 2;
	data->oplist[index]->args = \
	data->oplist[index]->args << 3 | (1 << (arg_code -1));
	add_byte_to_op(data, index, arg_code, tmp_index);
	data->oplist[index]->arg_count++;
	return (arg);
}

void	seperate_instruction(t_asmdata *data, char *ptr, int index, int i)
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
		if (args[j][start] == DIRECT_CHAR || args[j][start] == LABEL_CHAR \
			|| args[j][start] == 'r' || ft_isdigit(args[j][start]) \
			|| (args[j][start] == '-' && ft_isdigit(args[j][start + 1])))
			data->oplist[index]->arg[j] = trim_arg(data, args[j], index, start);
		j++;
	}
	while (j++ < 3)
	{
		data->oplist[index]->argcode = data->oplist[index]->argcode << 2;
		data->oplist[index]->args = data->oplist[index]->args << 3;
	}
	if (!args)
		free_exit(data, "ft_strsplit fail", ERROR);
	ft_memdel((void **)&args);
}

void	validate_instruction(t_asmdata *data, char *ptr, int index, int i)
{
	u_int16_t	res;
	int			tmp_i;

	seperate_instruction(data, ptr, index, i);
	tmp_i = get_statement_index(data, data->oplist[index]->statement);
	res = data->oplist[index]->args & g_statements[tmp_i].args;
	if (data->oplist[index]->arg_count != g_statements[tmp_i].arg_count \
		|| res ^ data->oplist[index]->args)
		free_exit(data, "invalid arg type/count for statement", ERROR);
	// ft_printf("arg {%s} count = %d\n", ptr, data->oplist[index]->arg_count);
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
			validate_instruction(data, ptr, index, i);
		else if (!validate_label(data, ptr, index))
			free_exit(data, "Invalid instruction/label", ERROR);
		index++;
	}
}

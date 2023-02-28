/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:31:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/03/01 00:10:14 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_size(char *str, int code)
{
	int	len;

	len = ft_strlen(str);
	if (code == 1)
		if (len >= PROG_NAME_LENGTH)
			return (-1);
	if (code == 2)
		if (len >= COMMENT_LENGTH)
			return (-1);
	return (1);
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

void	check_instruction(t_asmdata *data, char *ptr, int index, int i)
{
	char		**args;
	u_int16_t	res;
	int			tmp_i;

	args = seperate_instruction(data, ptr, index, i);
	tmp_i = get_statement_index(data, data->oplist[index]->statement);
	res = data->oplist[index]->args & g_statements[tmp_i].args;
	if (data->oplist[index]->arg_count != g_statements[tmp_i].arg_count \
		|| res ^ data->oplist[index]->args)
	{
		free_args(args, data->oplist[index]->arg_count);
		ft_memdel((void **)&args);
		free_exit(data, "invalid arg type/count for statement", ERROR);
	}
}

static int	check_arg_label(t_asmdata *data, char *arg)
{
	int	check_idx;
	int	valid;

	valid = 0;
	check_idx = 0;
	while (check_idx < data->opcount)
	{
		if (data->oplist[check_idx]->label != NULL && valid == 0)
		{
			if (ft_strcmp(data->oplist[check_idx]->label, &arg[2]) == 0)
				valid = 1;
		}
		if (valid == 1)
			break ;
		check_idx += 1;
	}
	if (valid == 0)
		return (1);
	else
		return (0);
}

int	check_if_label_exists(t_asmdata *data)
{
	int	op_idx;
	int	arg_idx;

	op_idx = 0;
	while (op_idx < data->opcount)
	{
		arg_idx = 0;
		while (arg_idx < 3 && data->oplist[op_idx]->arg[arg_idx] != NULL)
		{
			if (ft_strstr(data->oplist[op_idx]->arg[arg_idx], "%:") != NULL)
			{
				if (check_arg_label(data, \
					data->oplist[op_idx]->arg[arg_idx]) == 1)
					return (1);
			}
			arg_idx += 1;
		}
		op_idx += 1;
	}
	return (0);
}

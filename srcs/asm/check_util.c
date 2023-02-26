/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:31:35 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/26 22:52:36 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_size(char *str, int code)
{
	int	len;

	len = ft_strlen(str);
	if (code == 1)
		if (len >= PROG_NAME_LENGTH)
			return (1);
	if (code == 2)
		if (len >= COMMENT_LENGTH)
			return (1);
	return (0);
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
	u_int16_t	res;
	int			tmp_i;

	seperate_instruction(data, ptr, index, i);
	tmp_i = get_statement_index(data, data->oplist[index]->statement);
	res = data->oplist[index]->args & g_statements[tmp_i].args;
	if (data->oplist[index]->arg_count != g_statements[tmp_i].arg_count \
		|| res ^ data->oplist[index]->args)
		free_exit(data, "invalid arg type/count for statement", ERROR);
}

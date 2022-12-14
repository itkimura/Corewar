/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:23:22 by leo               #+#    #+#             */
/*   Updated: 2022/12/14 20:47:46 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	validate_arg(char *arg)
{
	int		res;

	res = 1;
	if (arg[0] == DIRECT_CHAR)
	{
		ft_printf("check T_IND\n");
	}
	else if (arg[0] == LABEL_CHAR || arg[0] == '-' || ft_isdigit(arg[0]))
	{
		ft_printf("check T_IND\n");
	}
	else if (arg[0] == 'r')
	{
		ft_printf("check T_REG\n");
	}
	return (res);
}

static char	*trim_arg(t_asmdata *data, char *arg, int index, int start)
{
	int	end;

	end = start;
	while (arg[end] && arg[end] != ' ' && arg[end] != '\t' \
		&& arg[end] != COMMENT_CHAR && arg[end] != ALTERNATE_COMMENT_CHAR)
		end++;
	arg = ft_memmove((void *)&arg[0], (void *)&arg[start], end - start);
	arg[end - start] = '\0';
	if (!validate_arg(arg))
		free_exit(data, "invalid arg", ERROR);
	if (index == -1)
		return (NULL); //remove
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

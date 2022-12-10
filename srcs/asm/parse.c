/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:07:09 by leo               #+#    #+#             */
/*   Updated: 2022/12/10 23:13:07 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int parse_instruction(t_asmdata *data, char *line)
{
	if (!data)
		return (0);
	if (*line)
		ft_printf("%s\n", line);
	return (1);
}

int	parse(t_asmdata *data, char *line, int fd)
{
	int	res;

	res = 1;
	if (!line)
		return (0);
	if (data->name && data->comment)
		res = parse_instruction(data, line);
	else if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		data->name = store_cmd(data->header->prog_name, line, fd, 5);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		data->comment = store_cmd(data->header->comment, line, fd, 8);
	else if (line[0] == '.')
		return (0);
	else if (!res || !data->name || !data->comment)
		free_exit(data, "name or comment missing/invalid", ERROR);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:07:09 by leo               #+#    #+#             */
/*   Updated: 2022/12/09 11:17:38 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int store_cmd(char *ptr, char *line, int maxlen, int i)
{
	int	j;

	j = 0;
	if (line[i] != '\"' && line[i + 1] != '\"') //gets triggered why???
		return (0);
	if (line[i] == ' ')
		i++;
	while (line[i++] && j < maxlen)
	{
		if (line[i] == '\"')
			break ;
		ptr[j++] = line[i++];
	}
	if (!line[i] || line[i] != '\"')
		return (0);
	return (1);
}

static void	parse_cmd(t_asmdata *data, char *line)
{
	int	res;

	res = 0;
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		res = store_cmd(data->header->prog_name, line, PROG_NAME_LENGTH, 5);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		res = store_cmd(data->header->comment, line, COMMENT_LENGTH, 8);
	if (!res || !data)
		free_exit(data);
}

void	parse(t_asmdata *data, char *line)
{
	if (!line)
		return ;
	ft_printf("%s", line);
	if (line[0] == '.' && (line[1] == NAME_CMD_STRING[1] \
		|| line[1] == COMMENT_CMD_STRING[1]))
		parse_cmd(data, line);
	ft_printf("\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:07:09 by leo               #+#    #+#             */
/*   Updated: 2022/12/11 03:55:24 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	get_full_cmd(char *ptr, int fd, int j)
{
	size_t	ret;
	char	buf;

	ret = 1;
	if (ptr[j])
		ptr[j++] = '\n';
	while (ret && ptr[j])
	{
		ret = read(fd, &buf, 1);
		if (buf == '\"')
			break ;
		ptr[j++] = buf;
	}
	return (j);
}

static int store_cmd(char *ptr, char *line, int fd, int i)
{
	int		j;

	j = 0;
	if (line[i] == ' ')
		i++;
	if (line[i++] != '\"')
		return (0);
	while (line[i] && ptr[j])
	{
		if (line[i] == '\"')
			break ;
		ptr[j++] = line[i++];
	}
	if (line[i] != '\"')
		j = get_full_cmd(ptr, fd, j);
	ptr[j] = '\0';
	ft_strdel(&line);
	return (1);
}

static int store_op(t_asmdata *data, char *line, int fd)
{
	ft_strdel(&line);
	if (!data || !line || !fd)
		return (1);
	return (1);
}

int	parse(t_asmdata *data, char *line, int fd)
{
	int	res;

	res = 1;
	if (!(*line))
		ft_strdel(&line);
	else if (data->name && data->comment && *line)
		res = store_op(data, line, fd);
	else if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		data->name = store_cmd(data->header->prog_name, line, fd, 5);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		data->comment = store_cmd(data->header->comment, line, fd, 8);
	else if (line[0] == '.')
		ft_strdel(&line);
	else if (!res || !data->name || !data->comment)
		free_exit(data, "name or comment missing/invalid", ERROR);
	return (1);
}

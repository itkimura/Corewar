/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2022/12/13 09:28:57 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

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

static int	store_cmd(char *ptr, char *line, int fd, int i)
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

static int	store_op(t_asmdata *data, char *line, int fd)
{
	t_op	*tmp;
	int		ret;
	int		i;

	ret = 1;
	while (ret)
	{
		i = 0;
		if (data->opcount == data->opsize)
			resize_op_table(data);
		if (!init_op(&tmp, line))
			free_exit(data, MALLOCFAIL, ERROR);
		data->oplist[data->opcount++] = tmp;
		ret = get_next_line(fd, &line);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		while (!(*line) || *line == COMMENT_CHAR \
			|| *line == ALTERNATE_COMMENT_CHAR || !line[i])
		{
			ft_strdel(&line);
			ret = get_next_line(fd, &line);
		}
	}
	return (1);
}

static int	store_data(t_asmdata *data, char *line, int fd)
{
	int	res;

	res = 0;
	while (line[res] && (line[res] == ' ' || line[res] == '\t'))
		res++;
	if (!(*line) || !line[res])
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

int	read_input(t_asmdata *data, char *argv)
{
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	ret = 1;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		free_exit(data, "Open file failed", ERROR);
	if (!data)
		return (0);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret == 1)
			store_data(data, line, fd);
	}
	if (close(fd) == -1)
		free_exit(data, "Closing file failed", ERROR);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2023/02/26 23:09:48 by leo              ###   ########.fr       */
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
	while (ft_isspace(line[i]))
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
	if (!check_comment_after_arg(&line[i + 1]))
		return (0);
	ft_strdel(&line);
	return (1);
}

static int	store_op(t_asmdata *data, char *line, int fd, int ret)
{
	t_op	*tmp;
	int		i;

	while (ret)
	{
		if (data->opcount == data->opsize)
			resize_op_table(data);
		if (!init_op(&tmp, line))
			free_exit(data, MALLOCFAIL, ERROR);
		data->oplist[data->opcount++] = tmp;
		ret = get_next_line(fd, &line);
		while (ret)
		{
			i = 0;
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (line[i] && line[i] != COMMENT_CHAR \
				&& line[i] != ALTERNATE_COMMENT_CHAR)
				break ;
			ft_strdel(&line);
			ret = get_next_line(fd, &line);
		}
	}
	return (1);
}

static int	store_data(t_asmdata *data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i] || line[i] == COMMENT_CHAR || line[i] == ALTERNATE_COMMENT_CHAR)
		ft_strdel(&line);
	else if (data->name && data->comment && *line)
		i = store_op(data, line, fd, 1);
	else if (!data->name && !ft_strncmp(&(line[i]), NAME_CMD_STRING, 5))
	{
		data->name = store_cmd(data->header->prog_name, line, fd, i + 5);
		if (check_size(data->header->prog_name, 1) == 1)
			free_exit(data, "name size invalid", ERROR);
	}
	else if (!data->comment && !ft_strncmp(&line[i], COMMENT_CMD_STRING, 8))
	{
		data->comment = store_cmd(data->header->comment, line, fd, i + 8);
		if (check_size(data->header->comment, 2) == 1)
			free_exit(data, "comment size invalid", ERROR);
	}
	else if (!i || !data->name || !data->comment || line[i] == '.')
	{
		ft_strdel(&line);
		free_exit(data, "name/comment error or bad command", ERROR);
	}
	return (1);
}

int	read_input(t_asmdata *data, char *argv)
{
	char	*line;
	int		turn;
	int		ret;
	int		fd;

	line = NULL;
	turn = 0;
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
			turn += store_data(data, line, fd);
	}
	if ((ret == 0 && turn == 0)|| data->opcount == 0)
		free_exit(data, "empty file/incomplete command", ERROR);
	if (close(fd) == -1)
		free_exit(data, "Closing file failed", ERROR);
	return (1);
}

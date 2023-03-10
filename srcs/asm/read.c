/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2023/03/10 16:57:10 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

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
	if (!line[i] || line[i] == COMMENT_CHAR \
		|| line[i] == ALTERNATE_COMMENT_CHAR)
		ft_strdel(&line);
	else if (data->name && data->comment && *line)
		i = store_op(data, line, fd, 1);
	else if (!data->name && !ft_strncmp(&(line[i]), NAME_CMD_STRING, 5))
		data->name = store_cmd(data->header->prog_name, line, fd, i + 5);
	else if (!data->comment && !ft_strncmp(&line[i], COMMENT_CMD_STRING, 8))
		data->comment = store_cmd(data->header->comment, line, fd, i + 8);
	else if (!data->name || !data->comment || line[i] == '.')
		return (-1);
	return (i);
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
	check_last_byte_is_newline(data, fd);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (ret && store_data(data, line, fd) == -1)
			free_exit(data, "name/comment error or bad command", ERROR);
	}
	if (data->opcount == 0)
		free_exit(data, "empty file/incomplete command?#need2check", ERROR);
	if (close(fd) == -1)
		free_exit(data, "Closing file failed", ERROR);
	return (1);
}

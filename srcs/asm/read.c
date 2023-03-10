/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2023/03/10 15:39:01 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

static int	get_full_cmd(char *ptr, int fd, int *j)
{
	size_t	ret;
	char	buf;
	char *line;

	ret = 1;
	buf = 0;
	if (ptr[*j])
		ptr[(*j)++] = '\n';
	line = 0;
	while (ret && ptr[*j])
	{
		//ret = read(fd, &buf, 1);
		ret = get_next_line(fd, &line);
		//ft_printf("line = %s\n", line);
		int len = ft_strlen(line);
		for (int i = 0; i < len; i++)
			ptr[(*j)++] = line[i];
		if (line[len - 1] == '\"')
			break;
		//if (buf == '\"')
		//	break ;
		//ptr[(*j)++] = buf;
	}
	if (!ptr[*j] && buf != '\"')
		return (0);
	return (1);
}

/* store comment and name (cmd = command .*) */
static int	store_cmd(char *ptr, char *line, int fd, int i)
{
	int		j;
	int		res;

	j = 0;
	res = 1;
	//ft_printf("--- store_cmd ---\n");
	while (ft_isspace(line[i]))
		i++;
	if (line[i++] != '\"')
		res = 0;
	while (res && line[i] && ptr[j])
	{
		if (line[i] == '\"')
			break ;
		ptr[j++] = line[i++];
	}
	if (res && line[i] != '\"')
		res = get_full_cmd(ptr, fd, &j);
	else if (!check_comment_after_arg(&line[i + 1]))
		res = 0;
	ptr[j] = '\0';
	//ft_printf("final_comment = %s\n", ptr);
	ft_strdel(&line);
	return (res);
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

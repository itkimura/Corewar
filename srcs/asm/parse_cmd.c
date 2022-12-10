/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:49:52 by leo               #+#    #+#             */
/*   Updated: 2022/12/10 16:24:32 by leo              ###   ########.fr       */
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
	int	j;

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
	return (1);
}

void	parse_cmd(t_asmdata *data, char *line, int fd)
{
	int		res;

	res = 0;
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		res = store_cmd(data->header->prog_name, line, fd, 5);
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		res = store_cmd(data->header->comment, line, fd, 8);
	if (!res)
		free_exit(data);
}

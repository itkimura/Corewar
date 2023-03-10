/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2023/03/10 17:14:46 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

static bool	test_remaining(int i, int len, char *line)
{
	if (line)
	{
		while (++i < len)
		{
			if (ft_isspace(line[i]) == 0)
				return (false);
		}
		return (true);
	}
	return (false);
}

static int	add_lines(int len, char *ptr, int *j, char *line)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (line[i] == '\"')
			break ;
		ptr[(*j)++] = line[i];
		i++;
	}
	if (i == len)
		ptr[(*j)++] = '\n';
	return (i);
}

static int	get_full_cmd(char *ptr, int fd, int *j)
{
	size_t	ret;
	char	*line;
	int		len;
	int		i;

	i = 0;
	ret = 1;
	line = 0;
	if (ptr[*j])
		ptr[(*j)++] = '\n';
	while (ret && ptr[*j])
	{
		ret = get_next_line(fd, &line);
		len = ft_strlen(line);
		i = add_lines(len, ptr, j, line);
		if (line[i] == '\"')
			break ;
		ft_strdel(&line);
	}
	if (test_remaining(i, len, line) == false || !ptr[*j])
		return (ft_strdel(&line), 0);
	return (ft_strdel(&line), 1);
}

/* store comment and name (cmd = command .*) */
int	store_cmd(char *ptr, char *line, int fd, int i)
{
	int		j;
	int		res;

	j = 0;
	res = 1;
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
	ft_strdel(&line);
	return (res);
}

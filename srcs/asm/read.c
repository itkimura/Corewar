/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2022/12/10 15:28:17 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <fcntl.h>

int	read_input(t_asmdata *data, char *argv)
{
	char	*line;
	int		ret;
	int		fd;

	line = NULL;
	ret = 1;
	fd = open(argv, O_RDONLY);
	if (!data)
		return (0);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		parse(data, line, fd);
		ft_strdel(&line);
	}
	if (close(fd) == -1)
		free_exit(data);
	return (1);
}

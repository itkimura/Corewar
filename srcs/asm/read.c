/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:40:11 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 18:07:07 by leo              ###   ########.fr       */
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
		parse(data, line);
		ft_strdel(&line);
	}
	return (1);
}

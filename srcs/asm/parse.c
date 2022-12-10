/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:07:09 by leo               #+#    #+#             */
/*   Updated: 2022/12/10 15:50:44 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	parse(t_asmdata *data, char *line, int fd)
{
	if (!line)
		return ;
	// ft_printf("%s", line);
	if (line[0] == '.' && (line[1] == NAME_CMD_STRING[1] \
		|| line[1] == COMMENT_CMD_STRING[1]))
		parse_cmd(data, line, fd);
	// ft_printf("\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:07:09 by leo               #+#    #+#             */
/*   Updated: 2022/12/10 17:12:00 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	parse(t_asmdata *data, char *line, int fd)
{
	if (!line)
		return (0);
	if (line[0] == '.' && (line[1] == NAME_CMD_STRING[1] \
		|| line[1] == COMMENT_CMD_STRING[1]))
		return (parse_cmd(data, line, fd));
	else if (line[0] == '.')
		return (0);
	if (!data->name || !data->comment)
		free_exit(data, "name or comment missing", ERROR);
	// else
		//parse instructions
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:07:09 by leo               #+#    #+#             */
/*   Updated: 2022/12/08 21:24:19 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_cmd(t_asmdata *data, char *line)
{
	if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		return ;//store name
	else if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		return ;//store comment
	if (!data)
		return ;
}

void	parse(t_asmdata *data, char *line)
{
	if (!line)
		return ;
	if (line[0] == '.' && (line[1] == NAME_CMD_STRING[1] \
		|| line[1] == COMMENT_CMD_STRING[1]))
		parse_cmd(data, line);
	
}
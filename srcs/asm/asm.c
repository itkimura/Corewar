/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:19 by thle              #+#    #+#             */
/*   Updated: 2022/12/09 11:03:42 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_structs(t_asmdata *data)
{
	if (!init_statements_table(data) || !init_labels_table(data))
		free_exit(data);
	data->header = (header_t *)malloc(sizeof(header_t));
	if (!data->header)
		free_exit(data);
	ft_memset((void *)data->header->prog_name, 0, PROG_NAME_LENGTH + 1);
	ft_memset((void *)data->header->comment, 0, COMMENT_LENGTH + 1);
	data->header->magic = COREWAR_EXEC_MAGIC;
	data->header->prog_size = 0;
}

int	main(int argc, char **argv)
{
	t_asmdata	*data;

	if (argc != 2)
		return (0);
	data = (t_asmdata *)malloc(sizeof(t_asmdata));
	if (!data)
		return (1);
	init_structs(data);
	read_input(data, argv[1]);
	ft_printf("name: {%s}\n", data->header->prog_name);
	ft_printf("comment: {%s}\n", data->header->comment);
	return (0);
}

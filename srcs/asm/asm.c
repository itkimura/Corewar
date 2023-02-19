/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:19 by thle              #+#    #+#             */
/*   Updated: 2023/02/19 12:32:48 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_structs(t_asmdata *data)
{
	if (!init_statements_table(data) || !init_labels_table(data) \
		|| !init_op_table(&data->oplist, OPSIZE))
		free_exit(data, MALLOCFAIL, ERROR);
	data->header = (header_t *)malloc(sizeof(header_t));
	if (!data->header)
		free_exit(data, MALLOCFAIL, ERROR);
//	ft_bzero((char *)data->header->prog_name, PROG_NAME_LENGTH + 1);
	ft_memset((void *)data->header->prog_name, '#', PROG_NAME_LENGTH + 1);
	ft_memset((void *)data->header->comment, '#', COMMENT_LENGTH + 1);
	data->header->prog_name[PROG_NAME_LENGTH] = '\0';
	data->header->comment[COMMENT_LENGTH] = '\0';
	data->header->magic = COREWAR_EXEC_MAGIC;
	data->header->prog_size = 0;
	data->name = 0;
	data->comment = 0;
	data->opcount = 0;
	data->opsize = OPSIZE;
	data->leaks = false;
}

int	main(int argc, char **argv)
{
	t_asmdata	*data;

	if (argc < 2 || argc > 3)
		return (0);
	data = (t_asmdata *)malloc(sizeof(t_asmdata));
	if (!data)
		return (1);
	init_structs(data);
	if (argc == 3 && !ft_strcmp(argv[2], "-x"))
		data->leaks = true;
	read_input(data, argv[1]);
	parse_instructions(data);
	// ft_printf("JAMBON BEURRE\n");
//	print_oplist(data);
	// ft_printf("*******opsize == %d\n", data->opsize);
	write_to_file(data, argv[1]);
	// print_hashlabel(data);
	free_exit(data, NULL, SUCCESS);
	return (0);
}

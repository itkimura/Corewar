/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:19 by thle              #+#    #+#             */
/*   Updated: 2023/02/26 13:10:16 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_structs(t_asmdata *data)
{
	if (!init_statements_table(data) || !init_labels_table(data) \
		|| !init_op_table(&data->oplist, OPSIZE))
		free_exit(data, MALLOCFAIL, ERROR);
	data->header = (t_header *)malloc(sizeof(t_header));
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
int	check_file_nam(char *filename)
{
	int	name_idx;

	name_idx = 0;
	name_idx = ft_strlen(filename);
	if (name_idx >= 3 && filename[name_idx - 1] == 's' \
		&& filename[name_idx - 2] == '.')
		return (1);
	else
		return (0);
}

int	main(int argc, char **argv)
{
	t_asmdata	*data;

	if (argc < 2 || argc > 3)
		return (0);
	if (!check_file_nam(argv[1]))
	{
		ft_printf("File extension non valid");
		return (0);
	}
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
	ft_printf("Writing output program\n");
	// print_hashlabel(data);
	free_exit(data, NULL, SUCCESS);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:19 by thle              #+#    #+#             */
/*   Updated: 2023/03/01 01:04:42 by leo              ###   ########.fr       */
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

void	check_last_byte_is_newline(t_asmdata *data, int fd)
{
	char	c;

	c = '\0';
	lseek(fd, -1L, SEEK_END);
	if (read(fd, &c, 1) && c != '\n')
		free_exit(data, "no newline at the end of the file", ERROR);
	else
		lseek(fd, 0, SEEK_SET);
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
	if (check_if_label_exists(data) == 1)
		free_exit(data, "arg label reference doesn't exists", ERROR);
	// write_to_file(data, argv[1]);
	ft_printf("Writing output program\n");
	free_exit(data, NULL, SUCCESS);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:00:58 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 17:07:37 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* like atoi, convert bytes to decimal */
uint32_t bytes_to_decimal(unsigned char *bytes, int start_idx, int end_idx)
{
	uint32_t res;
	uint32_t tmp;
	int shifted_value;

	shifted_value = 0;
	res = 0;
	while (end_idx >= start_idx)
	{
		tmp = (uint32_t)bytes[end_idx];
		res = (tmp << shifted_value) | res;
		shifted_value += 8;
		end_idx--;
	}
	return (res);
}

/* Magic_header (4 byte)-> validate with COREWAR_EXEC_MAGIC */
bool validate_magic_header(int fd)
{
	unsigned char bytes[4];

	read(fd, bytes, 4);
	return (bytes_to_decimal(bytes, 0, 3) == COREWAR_EXEC_MAGIC);
}

/* validate_null */
bool validate_null(int fd)
{
	unsigned char bytes[4];

	read(fd, bytes, 4);
	return (bytes_to_decimal(bytes, 0, 3) == 0);
}

/* Champion name  (PROG_NAME_LENGTH) -> save it in program->name */
bool read_champion_name(t_program *program, int fd)
{
	read(fd, program->name, PROG_NAME_LENGTH);
	program->name[PROG_NAME_LENGTH] = '\0';
	return (true);
}

// /* validate it under CHAMP_MAX_SIZE and save it into t_program->exec_code_size */
bool validate_exec_code_size(t_program *program, int fd)
{
	unsigned char bytes[4];

	read(fd, bytes, 4);
	program->exec_code_size = bytes_to_decimal(bytes, 0, 3);
	return (program->exec_code_size <= CHAMP_MAX_SIZE);
}

// /* Champion comment (COMMENT_LENGT) -> save it in program->name */
bool read_champion_comment(t_program *program, int fd)
{
	read(fd, program->comment, COMMENT_LENGTH);
	program->comment[COMMENT_LENGTH] = '\0';
	return (true);
}

// /* Exec code (t_program->exec_code_size) -> malloc and save it in program->exec_code */
bool read_exec_code(t_program *program, int fd)
{
	char str[1];

	program->exec_code = (unsigned char *)malloc(program->exec_code_size + 1);
	if (program->exec_code == NULL)
		return (false);
	read(fd, program->exec_code, program->exec_code_size);
	program->exec_code[program->exec_code_size] = '\0';
	if (read(fd, str, 1) != 0)
		return (false);
	return (true);
}

/*
 * read the campion, go to each function to save data
 */
bool read_champion(t_program *program, char *argv, int fd)
{
	if (validate_magic_header(fd) == false)
		return (print_error(argv, INVALID_HEADER));
	read_champion_name(program, fd);
	if (validate_null(fd) == false)
		return (print_error(argv, INVALID_NULL));
	if (validate_exec_code_size(program, fd) == false)
		return (print_error(argv, INVALID_CHAMPION_SIZE));
	read_champion_comment(program, fd);
	if (validate_null(fd) == false)
		return (print_error(argv, INVALID_NULL));
	read_exec_code(program, fd);
	return (true);
}

// int main(int argc, char **argv)
// {
// 	if (argc < 1)
// 		ft_printf("argc is wrong!");
// 	else
// 	{
// 		int fd = open(argv[1], O_RDONLY);
// 		t_program *program = (t_program *)malloc(sizeof(t_program));
// 		if (read_champion(program, argv[1], fd) == true)
// 			print_program(program);
// 		if (program->exec_code != NULL)
// 			free(program->exec_code);
// 		free(program);
// 		close(fd);
// 	}
// 	return 0;
// }
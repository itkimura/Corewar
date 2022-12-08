/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:00:58 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 17:43:01 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* Magic_header (4 byte)-> validate with COREWAR_EXEC_MAGIC */
static bool	validate_magic_header(int fd)
{
	unsigned char	bytes[5];

	read_then_terminate_bytes(fd, bytes, 4);
	return (bytes_to_decimal(bytes, 0, 3) == COREWAR_EXEC_MAGIC);
}

/* validate_null */
static bool	validate_null(int fd)
{
	unsigned char	bytes[5];

	read_then_terminate_bytes(fd, bytes, 4);
	return (bytes_to_decimal(bytes, 0, 3) == 0);
}

/* validate it under CHAMP_MAX_SIZE and save it into t_program->exec_code_size */
static bool	validate_exec_code_size(t_program *program, int fd)
{
	unsigned char	bytes[5];

	read_then_terminate_bytes(fd, bytes, 4);
	program->exec_code_size = bytes_to_decimal(bytes, 0, 3);
	return (program->exec_code_size <= CHAMP_MAX_SIZE);
}

/*
 * Exec code (t_program->exec_code_size)
 * -> malloc and save it in program->exec_code 
 */
static bool	read_exec_code(t_program *program, int fd)
{
	char	str[1];

	program->exec_code = (unsigned char *)malloc(program->exec_code_size + 1);
	if (program->exec_code == NULL)
		return (false);
	read_then_terminate_bytes(fd, program->exec_code, program->exec_code_size);
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
	read_then_terminate_bytes(fd, program->name, PROG_NAME_LENGTH);
	if (validate_null(fd) == false)
		return (print_error(argv, INVALID_NULL));
	if (validate_exec_code_size(program, fd) == false)
		return (print_error(argv, INVALID_CHAMPION_SIZE));
	read_then_terminate_bytes(fd, program->comment, COMMENT_LENGTH);	
	if (validate_null(fd) == false)
		return (print_error(argv, INVALID_NULL));
	if (read_exec_code(program, fd) == false)
	{
		if (program->exec_code == NULL)
			return (print_error("read_champion()", MALLOC_FAIL));
		return (print_error(argv, EXTRA_CHAMPION_CODE));
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (argc < 1)
		ft_printf("argc is wrong!");
	else
	{
		int fd = open(argv[1], O_RDONLY);
		t_program *program = (t_program *)malloc(sizeof(t_program));
		if (read_champion(program, argv[1], fd) == true)
			print_program(program);
		if (program->exec_code != NULL)
			free(program->exec_code);
		free(program);
		close(fd);
	}
	return 0;
}

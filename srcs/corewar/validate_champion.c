/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:00:58 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/07 15:09:47 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* Magic_header (4 byte)-> validate with COREWAR_EXEC_MAGIC */
t_bool validate_magic_header(int fd)
{
	unsigned char bytes[5];
	read(fd, bytes, 4);
	bytes[5] = '\0';
	// validate
}

/* validate_null */
t_bool validate_null(int fd)
{

}

/* Champion name  (PROG_NAME_LENGTH) -> save it in program->name */
t_bool read_champion_name(t_program *program, int fd)
{

}

/* like atoi, convert bytes to decimal */
unsigned int bytes_to_decimal(unsigned char *bytes)
{
}
/* validate it under CHAMP_MAX_SIZE and save it into t_program->exec_code_size */
t_bool validate_exec_code(t_program *program, int fd)
{

}

/* Champion comment (COMMENT_LENGT) -> save it in program->name */
t_bool read_champion_comment(t_program *program, int fd)
{

}

/* Exec code (t_program->exec_code_size) -> malloc and save it in program->exec_code */
t_bool read_champion_comment(t_program *program, int fd)
{

}


/*
 * read the campion, go to each function to save data
*/
t_bool read_champion(t_program *program, int fd)
{
	validte_magic_header(fd);
	read_champion_name(program, fd);
	validate_null(fd);
	validte_exec_code(program, fd);
	read_champion_comments(program, fd);
	validate_null(fd);
	read_exec_code();
}

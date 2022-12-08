/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:48 by thle              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/12/08 14:37:06 by thle             ###   ########.fr       */
=======
/*   Updated: 2022/12/08 13:28:08 by itkimura         ###   ########.fr       */
>>>>>>> 0b90016c95fbd90793ae4d15269fdba103d5b5c5
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdbool.h>
# include <string.h>

# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# define TOTAL_FLAGS 2

# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[33m"
# define BOLD "\e[1m"
# define RESET "\e[m"

/*
 * t_bool struct
 */
typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

/*
 * struct for flag
 * rmb to update TOTAL_FLAGS
*/
typedef enum e_vm_flag
{
	NOT_FLAG = -1,
	FLAG_N,
	FLAG_DUMP
} t_vm_flag;

/* 
 * error enum
 */
typedef enum e_error{
	MALLOC_FAIL,
	WRONG_NB,
	OPEN_FAIL,
	DUP_PLAYER_NB,
} t_error;

/* 
 * cattiage struct
 */
typedef struct s_program
{
	int32_t registry[REG_NUMBER];
	// r1: will be champion's code but minus
	// the rest: 0
	int32_t pc;
	t_bool carry; //-> 0?
	t_bool fix_position; //false -> -n -> true
	unsigned int  exec_code_size;
	unsigned char comment[COMMENT_LENGTH + 1];
	unsigned char name[PROG_NAME_LENGTH + 1];
	unsigned char *exec_code;
} t_program;

/* 
 * struct for general data of the game
*/
typedef struct s_game
{
	int total_players; //initialize 0
	t_program *player_array[MAX_PLAYERS];
	int flags_value[TOTAL_FLAGS]; //initialize to 0
}	t_game;


/*
 * corewar.c
 * main starts here
*/
t_bool	init_game(t_game **game);
t_bool	init_program(t_program **new, t_game *game);
void	store_palyer_number(t_game *game, t_program *program);
t_bool	validate_champion(char *file_path, t_game *game);
t_bool	validate_argv(int argc, char **argv);

/*
 * print.c
*/
t_bool	print_error(char *str, t_error error);
void	print_help(char *file_path);
void	print_program(t_program *program);
void	print_game(t_game *game);

/*
 * validate_champion.c
*/
t_bool validate_magic_header(int fd);
t_bool validate_null(int fd);
t_bool read_champion_name(t_program *program, int fd);
uint32_t bytes_to_decimal(unsigned char *bytes, int start_idx, int end_idx);
t_bool validate_exec_code_size(t_program *program, int fd);
t_bool read_champion_comment(t_program *program, int fd);
t_bool read_exec_code(t_program *program, int fd);
t_bool read_champion(t_program *program, int fd);

/*
 * validate_flag.c
*/
t_bool validate_n_flag_nb(char *argv, t_vm_flag *flag, t_game *game);
t_bool which_flag(char **argv, int index, t_vm_flag *flag, t_game *game);


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:48 by thle              #+#    #+#             */
/*   Updated: 2022/12/07 15:46:47 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <fcntl.h>


# include <string.h>

# define TOTAL_FLAGS 2

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
typedef enum e_flag
{
	NOT_FLAG = -1,
	FLAG_N,
	FLAG_DUMP
} t_flag;

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
 * cattiage struct
 */
typedef struct s_program
{
	int32_t registry[16];
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
 * error enum
 */
typedef enum e_error{
	MALLOC_FAIL,
} t_error;

/*
 * corewar.c
 * main starts here
*/
int init_game(t_game *game);
t_bool get_then_init_program(t_program **new);
void store_palyer_number(t_game *game, t_program *program);
t_bool champion_validation(char *str, t_game *game);
int validate_argv(int argc, char **argv);

/*
 * print.c
*/
void print_error(char *str, t_error error);
void print_help(void);


/*
 * validate_champion.c
*/
t_bool validate_magic_header(int fd);
t_bool validate_null(int fd);
t_bool read_champion_name(t_program *program, int fd);
unsigned int bytes_to_decimal(unsigned char *bytes);
t_bool validate_exec_code(t_program *program, int fd);
t_bool read_champion_comment(t_program *program, int fd);
t_bool read_exec_code(t_program *program, int fd);
t_bool read_champion(t_program *program, int fd);

/*
 * validate_flag.c
*/
t_bool validate_n_flag_nb(char *argv, int index, t_flag *flag);
t_bool which_flag(char *argv, int index, t_flag *flag);


#endif

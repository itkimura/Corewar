/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:48 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 18:18:50 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
#define COREWAR_H

#include <fcntl.h>
#include <stdbool.h>
#include <string.h>

#include "op.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#define TOTAL_FLAGS 5

#define RED "\e[31m"
#define GREEN "\e[32m"
#define BLUE "\e[33m"
#define BOLD "\e[1m"
#define RESET "\e[m"

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
typedef enum e_error
{
	MALLOC_FAIL,
	WRONG_NB,
	OPEN_FAIL,
	DUP_PLAYER_NB,
	NO_PLAYER_AFTER_FLAG_N,
	INVALID_HEADER,
	INVALID_NULL,
	INVALID_CHAMPION_SIZE,
	EXTRA_CHAMPION_CODE
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
	bool carry;		   //-> 0?
	bool fix_position; // false -> -n -> true
	unsigned int exec_code_size;
	unsigned char comment[COMMENT_LENGTH + 1];
	unsigned char name[PROG_NAME_LENGTH + 1];
	unsigned char *exec_code;
} t_program;

/*
 * struct for general data of the game
 */
typedef struct s_game
{
	int total_players; // initialize 0
	t_program *player_array[MAX_PLAYERS + 1];
	int flags_value[TOTAL_FLAGS]; // initialize to 0
} t_game;

/*
 * corewar.c
 * main starts here
 */
bool init_game(t_game **game);
bool init_program(t_program **new, t_game *game);
void store_palyer_number(t_game *game, t_program *program);
bool validate_champion(char *file_path, t_game *game);
bool validate_argv(int argc, char **argv);

/*
 * print.c
 */
bool print_error(char *str, t_error error);
void print_help(char *file_path);
void print_program(t_program *program);
void print_game(t_game *game);
void print_bits(uint32_t nbr, int size);

/*
 * validate_champion.c
 */
bool read_champion(t_program *program, char *argv, int fd);

/*
 * validate_flag.c
 */
bool validate_n_flag_nb(char *argv, t_vm_flag *flag, t_game *game);
bool which_flag(char **argv, int *index, t_vm_flag *flag, t_game *game);

/*
 * calc_utils.c
 */
uint32_t	bytes_to_decimal(unsigned char *bytes, int start_idx, int end_idx);

/*
 * read_utils.c
 */
void	read_then_terminate_bytes(int fd, unsigned char *bytes, int size);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:48 by thle              #+#    #+#             */
/*   Updated: 2023/01/02 13:10:23 by itkimura         ###   ########.fr       */
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

#define TOTAL_FLAGS 4

#define RED "\e[31m"
#define GREEN "\e[32m"
#define BLUE "\e[33m"
#define BOLD "\e[1m"
#define RESET "\e[m"


typedef enum e_arg
{
	FIRST_ARG,
	SECOND_ARG,
	THIRD_ARG
} t_arg;

/*
 * struct for flag
 * rmb to update TOTAL_FLAGS
 */
typedef enum e_vm_flag
{
	NOT_FLAG = -1,
	FLAG_N,
	FLAG_DUMP,
	FLAG_V,
	FLAG_A,
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
	MISSING_PLAYER,
	TOO_MANY_PLAYERS,
	INVALID_HEADER,
	INVALID_NULL,
	INVALID_CHAMPION_SIZE,
	EXTRA_CHAMPION_CODE
} t_error;

/*
 * carriage struct
 */
typedef struct s_carriage
{
	int32_t registry[REG_NUMBER];
	unsigned int id;
	bool carry; //-> false

	uint16_t statement_code;
	uint32_t last_live_performed;
	uint32_t remaining_cycle;
	uint32_t pc;
	uint32_t crossed_bytes;

	unsigned char	arg[4];
	int32_t			arg_value[4];

	struct s_carriage *next;

} t_carriage;

/*
 * cattiage struct
 */
typedef struct s_player
{
	// r1: will be champion's code but minus
	// the rest: 0
	unsigned int exec_code_size;
	bool fix_position;
	unsigned char comment[COMMENT_LENGTH + 1];
	unsigned char name[PROG_NAME_LENGTH + 1];
	unsigned char *exec_code;
} t_player;

/*
 * struct for general data of the game
 */
typedef struct s_game
{
	int total_players; // initialize 0
	t_player *players_in_order[MAX_PLAYERS];
	t_player *all_players[MAX_PLAYERS];
	int total_tmp_players;
	int flags_value[TOTAL_FLAGS]; // initialize to 0

	int cycles_to_die;
	int winner;					  // could be t_player
	int number_of_cycles;		  // for the entire run
	int number_of_live_statement; // for the last cycles_to_die
	int number_of_check;

	t_carriage *carriage_head;
	unsigned char arena[MEM_SIZE];
} t_game;


/*
 * op_tab
*/
typedef struct s_op
{
	char			*name;
	int				nbr_arg;
	unsigned char	arg[3];
	unsigned char	op_code;
	int				cycles;
	bool			arg_code_type;
	int				t_dir_size;
	bool			(*f)(t_game *game, t_carriage *s_carriage);
}	t_op;

/*
 * corewar.c
 */
bool init_game(t_game **game);
bool init_player(t_player **new, t_game *game);
void store_palyer_number(t_game *game, t_player *player);
bool validate_champion(char *file_path, t_game *game);
bool validate_argv(int argc, char **argv);

/*
 * update_players_array.c
 */
bool add_player(t_player *new, t_game *game);
bool update_players_array(t_game *game);

/*
 * init_structure.c
 */
bool init_game(t_game **game);
void ft_unsigned_char_zero(unsigned char *str, int len);
bool init_player(t_player **new, t_game *game);
bool init_carriage(t_carriage **new, int id);

/*
 * free_all.c
 */
void free_player(t_player *p);
void free_game(t_game *game);
void free_all(t_game *game);

/*
 * print.c
 */
bool print_error(char *str, t_error error);
void print_help(char *file_path);
void	print_v(t_game *game, t_carriage *carriage, int shift);

void print_single_player(t_player *player);
void print_all_players(t_game *game);
void print_game(t_game *game);
void print_bits(uint32_t nbr, int size);
void print_single_carriage(t_carriage *head);
void print_carriage_list(t_carriage *head);
void print_arg_and_val(t_carriage *carriage);

/*
 * validate_champion.c
 */
bool read_champion(t_player *player, char *argv, int fd);
bool validate_champion(char *file_path, t_game *game);

/*
 * validate_flag.c
 */
bool validate_n_flag_nb(char *argv, t_vm_flag *flag, t_game *game);
bool which_flag(char **argv, int *index, t_vm_flag *flag, t_game *game);

/*
 * calc_utils.c
 */
int reverse_bytes(unsigned char *bytes, unsigned int pos, int nbytes);

/*
 * read_utils.c
 */
void read_then_terminate_bytes(int fd, unsigned char *bytes, int size);

/* 
 * op.c
 */
extern t_op	g_op_tab[16];

/*
 * operation functions
 */
bool	op_live(t_game *game, t_carriage *carriage);
bool	op_ld(t_game *game, t_carriage *carriage);
bool	op_lld(t_game *game, t_carriage *carriage);
bool	op_add(t_game *game, t_carriage *carriage);
bool	op_sub(t_game *game, t_carriage *carriage);
bool	op_and(t_game *game, t_carriage *carriage);
bool	op_or(t_game *game, t_carriage *carriage);
bool	op_xor(t_game *game, t_carriage *carriage);

bool	op_st(t_game *game, t_carriage *carriage);
bool	op_sti(t_game *game, t_carriage *carriage);
bool	op_ldi(t_game *game, t_carriage *carriage);
bool	op_lldi(t_game *game, t_carriage *carriage);
bool	op_fork(t_game *game, t_carriage *carriage);
bool	op_lfork(t_game *game, t_carriage *carriage);
bool	op_zjmp(t_game *game, t_carriage *carriage);
bool	op_aff(t_game *game, t_carriage *carriage);

/*
 * op_utils.c
 */
bool add_carriage(t_game *game, t_carriage *src, unsigned int dst_pc);

/*
 * get_arg.c
 */
bool get_arg_value(t_carriage *carriage, unsigned char *arena);

/*
 * get_value.c
 */
int get_value(t_game *game, t_carriage *carriage, int order, bool mod);



#endif

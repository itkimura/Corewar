/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:59:48 by thle              #+#    #+#             */
/*   Updated: 2023/02/22 14:50:51 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdbool.h>
# include "op.h"
# include "libft.h"
# include "ft_printf.h"

/*library for bonus*/
# include <stdio.h>

# define TOTAL_FLAGS 7

# define RED "\e[31m"
# define GREEN "\e[32m"
# define BLUE "\e[33m"
# define BOLD "\e[1m"
# define RESET "\e[m"

# define INITIAL_VALUE -1

enum	e_arg
{
	FIRST_ARG,
	SECOND_ARG,
	THIRD_ARG
};

/*
 * struct for flag
 * rmb to update TOTAL_FLAGS
 */
typedef enum e_vm_flag
{
	NOT_FLAG = -1,
	FLAG_DUMP,
	FLAG_N,
	FLAG_L,
	FLAG_V,
	FLAG_A,
	FLAG_S,
	FLAG_LLD
}				t_vm_flag;

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
}				t_error;

/*
 * operation
 */
enum e_op
{
	OP_LIVE,
	OP_LD,
	OP_ST,
	OP_ADD,
	OP_SUB,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_ZJMP,
	OP_LDI,
	OP_STI,
	OP_FORK,
	OP_LLD,
	OP_LLDI,
	OP_LFORK,
	OP_AFF
};

/*
 * options value
 * 0 : Show only essentials
 * 1 : Show lives
 * 2 : Show cycles
 * 4 : Show operations (Params are NOT litteral ...)
 * 8 : Show deaths
 * 16 : Show PC movements (Except for jumps)
 */
enum	e_flag_options
{
	FO_ESSENTIALS,
	FO_LIVES,
	FO_CYCLES,
	FO_OPERAIONS = 4,
	FO_DEATHS = 8,
	FO_ADV = 16
};

/*
 * carriage struct
 */
typedef struct s_carriage
{
	int					registry[REG_NUMBER];
	int					arg[4];
	int					arg_value[4];
	unsigned int		id;
	unsigned int		pc;
	unsigned int		next_statement_pc;
	int					last_live_performed;
	int					remaining_cycle;
	short int			statement_index;
	bool				carry;
	struct s_carriage	*next;
}						t_carriage;

/*
 * cattiage struct
 */
typedef struct s_player
{
	unsigned char	comment[COMMENT_LENGTH + 1];
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	*exec_code;
	unsigned int	exec_code_size;
	bool			fix_position;
	t_carriage		*carriage;
}					t_player;

/*
 * struct for general data of the game
 */
typedef struct s_game
{
	unsigned char	arena[MEM_SIZE];
	t_player		*players_in_order[MAX_PLAYERS];
	t_player		*all_players[MAX_PLAYERS];
	int				flags_value[TOTAL_FLAGS];
	int				total_players;
	int				total_tmp_players;
	int				cycles_to_die;
	int				winner;
	int				total_cycles;
	int				check_counter;
	int				total_lives;
	int				total_checks;
	int				total_carriages;
	t_carriage		*carriage_head;
}					t_game;

/*
 * op_tab
 */
typedef bool	((*t_f)(t_game *game, t_carriage *s_carriage));

typedef struct s_op
{
	char	*name;
	int		nbr_arg;
	int		arg[3];
	int		op_code;
	int		cycles;
	bool	arg_code_type;
	int		t_dir_size;
	t_f		f;
}			t_op;

/*
 * corewar.c
 */
bool	init_game(t_game **game);
bool	init_player(t_player **new, t_game *game);
bool	validate_champion(char *file_path, t_game *game);
bool	validate_argv(int argc, char **argv);

/*
 * run_game.c
 */
bool	run_game(t_game *game);

/*
 * update_players_array.c
 */
bool	add_player(t_player *new, t_game *game);
bool	update_players_array(t_game *game);

/*
 * init_structure.c
 */
bool	init_game(t_game **game);
bool	init_player(t_player **new, t_game *game);
bool	init_carriage(t_carriage **new, t_player *player, int id);
void	init_arena(t_game *game);

/*
 * free_all.c
 */
void	free_player(t_player *p);
void	free_game(t_game *game);
void	free_all(t_game *game);

/*
 * print.c
 */
bool	print_error(char *str, t_error error);
void	print_help(char *file_path);
void	print_adv(t_game *game, t_carriage *carriage, int shift);
void	print_arena(t_game *game);

/*
 * print_flag.c
 */
bool	print_dump(t_game *game);
void	flag_l(t_game *game, t_carriage *carriage);
void	print_flag_l_death(t_game *game, t_carriage *carriage);

/*
 * validate_champion.c
 */
bool	validate_champion(char *file_path, t_game *game);

/*
 * flag.c
 */
bool	is_number(char *argv);
bool	is_after_flag_n(t_game *game);
bool	which_flag(char **argv, int *index, t_vm_flag *flag, t_game *game);

/* 
 * flag_utils.c
 */
bool	validate_n_flag(char *argv, t_vm_flag *flag, t_game *game);
bool	validate_d_flag(char *argv, t_vm_flag *flag, t_game *game);
bool	validate_l_flag(char *argv, t_vm_flag *flag, t_game *game);
bool	validate_a_flag(t_vm_flag *flag, t_game *game);
bool	validate_s_flag(char *argv, t_vm_flag *flag, t_game *game);

/*
 * utils.c
 */
int		char_to_int(unsigned char *bytes,
			unsigned int pos, int nbytes, bool is_arena);
bool	is_op_code(char c);
void	kill_carriage(t_game *game, t_carriage *prev,
			t_carriage *curr, t_carriage *next);

/*
 * op.c
 */
extern t_op		g_op_tab[16];

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
bool	add_carriage(t_game *game, t_carriage *src, unsigned int dst_pc);

/*
 * get_arg.c
 */
bool	get_arg_value(t_carriage *carriage, unsigned char *arena);

/*
 * get_value.c
 */
int		get_value(t_game *game, t_carriage *carriage, int order, bool mod);

/*
 place_value.c
 */
void	place_value(t_game *game, int value, int pos);

#endif

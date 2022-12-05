/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:56 by thle              #+#    #+#             */
/*   Updated: 2022/12/05 14:52:52 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include <string.h>

# define TOTAL_FLAGS 2

typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

/* rmb to update TOTAL_FLAGS */
typedef enum e_flag
{
	FLAG_N,
	FLAG_DUMP
} t_flag;

typedef struct s_game
{
	int total_players; //initialize 0
	t_carriage *player_array[MAX_PLAYERS];
	int flags_value[TOTAL_FLAGS]; //initialize to 0
	
}	t_game;

typedef struct s_carriage
{
	int32_t registry[16];
	// r1: will be champion's code but minus
	// the rest: 0
	int32_t pc;
	t_bool carry; //-> 0?
	char *comment;
	char *name;
} t_carriage;

/* ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ... */


/* init game t_game struct */
int init_game(t_game *game)
{
	
}

/*
return which flag by ft_strcmp
*/
t_flag which_flag(char *arv)
{
	// if (ft_strcmp(arv, "-d") == 0)
	// 	return (FLAG_DUMP);
	// if (ft_strcmp(arv, "-n") == 0){
	// 	return ()
	// }
	// return (0);
}

t_bool get_then_init_carriage(t_carriage **new)
{
	*new = (t_carriage *)malloc(sizeof(t_carriage));
	if (new == NULL)
		return (FALSE);
	//init new
	//Check if flag_value[Flag_n] -> t_carriage new, new.r[0] = flag_value[FLAG_N];
	//flag_value[flag_n] = 0;
}

t_bool champion_validation(char *str, t_game *game)
{
	int fd = open(str, O_RDONLY);
	t_carriage *new;

	new = NULL;
	if (fd < 0)
		return FALSE;
	if (get_then_init_carriage(new) == NULL) return FALSE;
	/* read then validate */

	close(fd);
}

/*
while loop each argv
call get_arg_type
	if flag, check which flag
		if FLAG_DUMP &&  => t_game->flag_value[FLAG_DUMP] = atoi(argv)
	if CHAMPION -> open ->  init_carriage -> 
	->read -> validation_champion; t_game->total_players++;
*/
int validation(int argc, char **argv)
{
	int flag;
	int index;

	flag = -1;
	index = 1;
	while (index < argc)
	{
		flag = which_flag(argv[index]);
		if (flag != -1)
		{
			if (is_number(argv[++index]) == TRUE)
			{
				t_game->flag_value[FLAG_DUMP] = ft_atoi(arv);
				flag = -1;
			}
			else
				ERROR
			
		}
		else
		{
			//champion validation
		}
		index++;
	}
}

int main(int argc, char *argv[])
{
	// Branch 'vm' set up to track remote branch 'vm' from 'origin'.
	// ./corewar [-dump nbr_cycles] [[-n number] champion1.cor]

	/*
	if argc < 2:
		print help
	else:
		start testing

	*/

	return (0);
}
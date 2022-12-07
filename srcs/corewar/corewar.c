/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:55:56 by thle              #+#    #+#             */
/*   Updated: 2022/12/07 16:21:24 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* init game t_game struct */
int init_game(t_game *game)
{
	
}

t_bool get_then_init_program(t_program **new)
{
	*new = (t_program *)malloc(sizeof(t_program));
	if (new == NULL)
		return (FALSE);
	//init new
	//Check if flag_value[Flag_n] -> t_program new, new.r[0] = flag_value[FLAG_N];
	//flag_value[flag_n] = 0;
}

/*
 * store_player number
 * if game->flag_value[FLAG_N] != 0 -> program->registry[0]
 * Check game->player_array[nb] != 0) -> swap and put into the next one
 *
 * else
 *  program->registory[total_players] = program;
 *  total_players++;
*/
void store_palyer_number(t_game *game, t_program *program)
{

}

/*
 * open file -> if it's fail, it means the file is not exist.
 * if success
 * 1. Make program structure
 * 2. Start reading and save info into program
*/

t_bool champion_validation(char *str, t_game *game)
{
	int fd = open(str, O_RDONLY);
	t_program *new;

	new = NULL;
	if (fd < 0)
		return FALSE;
	if (get_then_init_program(new) == NULL)
		return FALSE;
	/* read then validate */
	close(fd);
}

/*
while loop each argv
call get_arg_type
	if flag, check which flag
		if FLAG_DUMP &&  => t_game->flag_value[FLAG_DUMP] = atoi(argv)
	if CHAMPION -> open ->  init_program -> 
	->read -> validation_champion; t_game->total_players++;
*/
int validate_argv(int argc, char **argv)
{
	int flag;
	int index;

	flag = -1;
	index = 1;
	while (index < argc)
	{
		if (which_flag(argv, index, &flag) == FALSE)
			ft_printf("ERRPOR");
		if (flag = NOT_FLAG)
		{
			//champion validation
		}
		flag = NOT_FLAG;
		index++;
	}
}

/*
 * Check the number of args, and it is only one print help text
 * if there are some arguments, start validation.
*/
int main(int argc, char *argv[])
{
	// Branch 'vm' set up to track remote branch 'vm' from 'origin'.
	// ./corewar [-dump nbr_cycles] [[-n number] champion1.cor]
	/*
	if argc < 2:
		print_help();
	else:
		start testing
	*/
	return (0);
}

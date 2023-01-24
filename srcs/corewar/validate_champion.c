/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_champion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:00:58 by itkimura          #+#    #+#             */
/*   Updated: 2023/01/24 16:07:45 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"
#define VALIDATE_MAGIC_HEADER 1
#define VALIDATE_NULL 2
#define VALIDATE_EXEC_CODE_SIZE 3

static void	read_then_terminate_bytes(int fd, unsigned char *bytes, int size)
{
	read(fd, bytes, size);
	bytes[size] = '\0';
}

static bool validate(int fd, int type, t_player *player)
{
	unsigned char bytes[5];

	read_then_terminate_bytes(fd, bytes, 4);
	if (type == VALIDATE_MAGIC_HEADER)
		return (char_to_int(bytes, 0, 4, false) == COREWAR_EXEC_MAGIC);
	else if (type == VALIDATE_NULL)
		return (char_to_int(bytes, 0, 4, false) == 0);
	else if (type == VALIDATE_EXEC_CODE_SIZE)
	{
		player->exec_code_size = char_to_int(bytes, 0, 4, false);
		return (player->exec_code_size <= CHAMP_MAX_SIZE);
	}
	return (false);
}

/*
 * Exec code (t_player->exec_code_size)
 * -> malloc and save it in player->exec_code
 */
static bool	read_exec_code(t_player *player, int fd)
{
	char	str[1];

	player->exec_code = (unsigned char *)malloc(player->exec_code_size + 1);
	if (player->exec_code == NULL)
		return (false);
	read_then_terminate_bytes(fd, player->exec_code, player->exec_code_size);
	player->exec_code[player->exec_code_size] = '\0';
	if (read(fd, str, 1) != 0)
		return (false);
	return (true);
}

/*
 * read the campion, go to each function to save data
 */
bool	read_champion(t_player *player, char *argv, int fd)
{
	if (validate(fd, VALIDATE_MAGIC_HEADER, player) == false)
		return (print_error(argv, INVALID_HEADER));
	read_then_terminate_bytes(fd, player->name, PROG_NAME_LENGTH);
	if (validate(fd, VALIDATE_NULL, player) == false)
		return (print_error(argv, INVALID_NULL));
	if (validate(fd, VALIDATE_EXEC_CODE_SIZE, player) == false)
		return (print_error(argv, INVALID_CHAMPION_SIZE));
	read_then_terminate_bytes(fd, player->comment, COMMENT_LENGTH);
	if (validate(fd, VALIDATE_NULL, player) == false)
		return (print_error(argv, INVALID_NULL));
	if (read_exec_code(player, fd) == false)
	{
		if (player->exec_code == NULL)
			return (print_error("read_champion()", MALLOC_FAIL));
		return (print_error(argv, EXTRA_CHAMPION_CODE));
	}
	return (true);
}

/*
 * 1. open -> if it's fail, it means the file is not exist.
 * 1. Make player structure
 * 2. Start reading and save info into player
 */
bool	validate_champion(char *file_path, t_game *game)
{
	int			fd;
	t_player	*new;

	if (game->total_players >= MAX_PLAYERS)
		return (print_error(file_path, TOO_MANY_PLAYERS));
	new = NULL;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (print_error(file_path, OPEN_FAIL));
	if (init_player(&new, game) == false)
		return (close(fd), false);
	if (read_champion(new, file_path, fd) == false)
		return (close(fd), false);
	close(fd);
	return (true);
}

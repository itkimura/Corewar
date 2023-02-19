/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:50:45 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/17 12:59:58 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_name(t_asmdata *data, int fd)
{
	int		i;
	char	buffer[PROG_NAME_LENGTH];
//	int32_t	helper;

	i = 0;
	ft_printf("**********PROG_NAME + NULL + LEN*********\n");
	ft_bzero(buffer, PROG_NAME_LENGTH);
	while (i < PROG_NAME_LENGTH)
	{
		if (data->header->prog_name[i] != '#')
			buffer[i] = (int)data->header->prog_name[i];
		else if (data->header->prog_name[i] == '#')
			buffer[i] = 0;
		i++;
	}
	write(fd, buffer, PROG_NAME_LENGTH);
	write(fd, NULL, 4);
	write(fd, "\0\0\0\0", 4);
//	helper = byte_shift_translate(data->opsize);
	//write(fd, &helper, 4);
}

void	write_comment(t_asmdata *data, int fd)
{
	int		i;
	char	buffer[COMMENT_LENGTH];

	ft_printf("**********COMMENT*********\n");
	i = 0;
	ft_bzero(buffer, PROG_NAME_LENGTH);
	while (i < COMMENT_LENGTH)
	{
		if (data->header->comment[i] != '#')
			buffer[i] = (int)data->header->comment[i];
		else if (data->header->comment[i] == '#')
			buffer[i] = 0;
		i++;
	}
	write(fd, buffer, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
}

void	write_size(t_asmdata *data, int fd)
{
	int	buffer;
	int	i;

	i = 0;
	while (data->oplist[i])
		i++;
	buffer = data->oplist[i - 1]->totalbyte;
//	ft_printf("buffer == %d, size == %d, i == %d\n", buffer, data->header->prog_size, i);
	buffer = byte_shift_translate(buffer);
	write(fd, &buffer, 4);
	/*
	ft_bzero(buffer, 4);
	while(i >= 0)
	{
		buffer[j] = (char)data->header->prog_size;
		i--;
		j++;
	}
	write(fd, buffer, 4);
	*/
}

char	*change_filename(char *filename)
{
	int name_idx;

	name_idx = 0;
	name_idx = ft_strlen(filename);
	while (filename[name_idx] != '.')
		name_idx++;
	filename[name_idx] = '\0';
	filename = ft_strjoin(filename, ".cor");
	ft_printf("file name == %s\n", filename);
	return (filename);
}

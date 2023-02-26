/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:50:45 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/26 11:53:26 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_name(t_asmdata *data, int fd)
{
	int		i;
	int		len;
	char	buffer[PROG_NAME_LENGTH];
//	int32_t	helper;

	i = 0;
	len = 0;
	len = ft_strlen(data->header->prog_name);
	ft_bzero(buffer, PROG_NAME_LENGTH);
	while (i <= PROG_NAME_LENGTH)
	{
		if (i <= len) 
		{
			buffer[i] = (int)data->header->prog_name[i];
		}
		else if (data->header->prog_name[i] == '#' && i > len)
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
	int		len;
	char	buffer[COMMENT_LENGTH];

	i = 0;
	len = ft_strlen(data->header->comment);
	ft_bzero(buffer, PROG_NAME_LENGTH);
	while (i <= COMMENT_LENGTH)
	{
		if (i <= len) 
			buffer[i] = (int)data->header->comment[i];
		else if (data->header->comment[i] == '#' && i > len)
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
	buffer = 0;
	while (data->oplist[i])
		i++;
	//ft_printf("data->oplist[i] == %d\n", data->oplist[i]->totalbyte);
	while (buffer == 0)
	{
		i--;
		buffer = data->oplist[i]->totalbyte;
	}
	//ft_printf("buffer == %d, size == %d, i == %d\n", buffer, data->header->prog_size, i);
	buffer = byte_shift_translate(buffer);
	//ft_printf("buffer == %d, size == %d, i == %d\n", buffer, data->header->prog_size, i);
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
//	name_idx = ft_strlen(filename);
	while (filename[name_idx] != '.')
		name_idx++;
	filename[name_idx] = '\0';
	filename = ft_strjoin(filename, ".cor");
	return (filename);
}

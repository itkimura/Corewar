/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 09:50:45 by ccariou           #+#    #+#             */
/*   Updated: 2023/03/02 15:13:17 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	byte_shift_translate(int value)
{
	int	converted;

	converted = 0;
	if (value)
	{
		converted |= ((0x000000ff & value) << 24);
		converted |= ((0x0000ff00 & value) << 8);
		converted |= ((0x00ff0000 & value) >> 8);
		converted |= ((0xff000000 & value) >> 24);
	}
	return (converted);
}

void	write_name(t_asmdata *data, int fd)
{
	int		i;
	int		len;
	char	buffer[PROG_NAME_LENGTH];

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
	while (buffer == 0 && i > 0)
	{
		i--;
		buffer = data->oplist[i]->totalbyte;
	}
	buffer = byte_shift_translate(buffer);
	write(fd, &buffer, 4);
}

char	*change_filename(char *filename)
{
	int		name_idx;
	char	*helper;

	name_idx = 0;
	while (filename[name_idx] != '.')
		name_idx++;
	filename[name_idx] = '\0';
	helper = ft_strjoin(filename, ".cor");
	return (helper);
}

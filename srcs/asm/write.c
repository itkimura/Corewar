/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:43:57 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/27 15:10:57 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

char	*translate_labels(t_asmdata *data, char *arg, int byte, int i)
{
	char	*percent;
	int		pos;

	i = -1;
	pos = 0;
	while (data->oplist[++i])
	{
		if (ft_strequ(data->oplist[i]->label, ft_strchr(arg, ':') + 1))
		{
			if ((arg)[0] == '%')
			{
				percent = ft_strdup("%");
				arg = ft_itoa(pos - byte);
				percent = ft_strjoin(percent, arg);
				if (!percent)
					return (0);
				arg = percent;
				return (arg);
			}
			arg = ft_itoa(pos - byte);
			return (arg);
		}
		pos += data->oplist[i]->byte;
	}
	return (0);
}

void	convert_label(t_asmdata *data)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	pos = 0;
	while (data->oplist[i])
	{
		j = 0;
		while (j < 3)
		{
			if (data->oplist[i]->arg[j] && \
				ft_strchr(data->oplist[i]->arg[j], ':'))
				data->oplist[i]->arg[j] = \
				translate_labels(data, data->oplist[i]->arg[j], pos, i);
			j++;
		}
		pos += data->oplist[i]->byte;
		i++;
	}
}
/*
 * statement
 * typecode
 * arg
 */

void	champ_code(t_op **data, int fd)
{
	int				i;
	int				j;
	unsigned char	buf;
	t_op			**tmp;

	i = 0;
	j = 0;
	tmp = data;
	if ((*tmp)->statement == NULL)
		return ;
	while (ft_strcmp((*tmp)->statement, g_statements[j].name) != 0)
		j++;
	buf = g_statements[j].code;
	write(fd, &buf, 1);
	buf = '0';
	if (g_statements[j].argcode == true && \
		ft_strcmp((*tmp)->statement, g_statements[j].name) == 0)
	{
		buf = (*tmp)->argcode;
		write(fd, &buf, 1);
	}
	buf = '0';
	if ((*tmp)->arg[i] == NULL)
		return ;
	convert_arg(tmp, fd, j);
}

void	write_to_file(t_asmdata *data, char *filename)
{
	char	*final_filename;
	int32_t	helper;
	int		i;
	int		fd;

	final_filename = change_filename(filename);
	if (!final_filename)
		return ;
	convert_label(data);
	i = 0;
	fd = open(final_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	i = 0;
	helper = byte_shift_translate(COREWAR_EXEC_MAGIC);
	write (fd, &helper, 4);
	write_name(data, fd);
	write_size(data, fd);
	write_comment(data, fd);
	while (data->oplist[i])
	{
		champ_code(&data->oplist[i], fd);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:43:57 by ccariou           #+#    #+#             */
/*   Updated: 2023/03/10 17:24:29 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>

static char	*label_helper(t_asmdata *data, char *str, int byte, int pos)
{
	char	*helper;

	if (str[0] == '%')
	{
		helper = ft_itoa(pos - byte);
		if (!helper)
			free_exit(data, MALLOCFAIL, ERROR);
		free(str);
		str = ft_strjoin("%", helper);
		ft_strdel(&helper);
		return (str);
	}
	free(str);
	str = ft_itoa(pos - byte);
	if (!str)
		free_exit(data, MALLOCFAIL, ERROR);
	return (str);
}

char	*translate_labels(t_asmdata *data, char *arg, int byte, int i)
{
	int		pos;

	i = -1;
	pos = 0;
	while (data->oplist[++i])
	{
		if (ft_strequ(data->oplist[i]->label, ft_strchr(arg, ':') + 1))
		{
			arg = label_helper(data, arg, byte, pos);
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
			{
				data->oplist[i]->arg[j] = \
				translate_labels(data, data->oplist[i]->arg[j], pos, i);
			}
			j++;
		}
		pos += data->oplist[i]->byte;
		i++;
	}
}

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

	final_filename = change_filename(data, filename);
	if (!final_filename)
		return ;
	convert_label(data);
	i = 0;
	fd = open(final_filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	ft_strdel(&final_filename);
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

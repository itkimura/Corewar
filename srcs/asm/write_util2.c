/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:19:08 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/27 14:23:50 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	check_arg(char *arg)
{
	if (!arg)
		return (0);
	if (ft_strchr(arg, '%'))
		return (DIR_CODE);
	if (ft_strchr(arg, 'r') && !ft_strchr(arg, LABEL_CHAR))
		return (REG_CODE);
	return (IND_CODE);
}

static void	arg_dir(t_op **tmp, int fd, int i, int j)
{
	int	dir;

	dir = ft_atoi(&(*tmp)->arg[i][1]);
	if (g_statements[j].size == 4)
	{
		write(fd, &((unsigned char *)&dir)[3], 1);
		write(fd, &((unsigned char *)&dir)[2], 1);
	}
	write(fd, &((unsigned char *)&dir)[1], 1);
	write(fd, &((unsigned char *)&dir)[0], 1);
}

void	convert_arg(t_op **tmp, int fd, int j)
{
	int				i;
	int				ind;
	int				check;
	unsigned char	buf;

	i = 0;
	while (i < 3)
	{
		check = check_arg((*tmp)->arg[i]);
		if (check == 1)
		{
			buf = ft_atoi(ft_strchr((*tmp)->arg[i], 'r') + 1);
			write(fd, &buf, 1);
		}
		else if (check == 2)
			arg_dir(tmp, fd, i, j);
		else if (check == 3)
		{
			ind = ft_atoi((*tmp)->arg[i]);
			write(fd, &((unsigned char *)&ind)[1], 1);
			write(fd, &((unsigned char *)&ind)[0], 1);
		}
		i++;
	}
}

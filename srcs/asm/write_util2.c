/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:19:08 by ccariou           #+#    #+#             */
/*   Updated: 2023/02/20 17:42:53 by ccariou          ###   ########.fr       */
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

void	convert_arg(t_op **tmp, int fd, int j)
{
	int				i;
	int				ind;
	int				dir;
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
		{
//			ft_printf("(j = %d, i = %d g_statements[j].size == %d\n", j, i, g_statements[j].size);
			dir = ft_atoi(&(*tmp)->arg[i][1]);
			if (g_statements[j].size == 4)
			{
				write(fd, &((unsigned char *)&dir)[3], 1);
				write(fd, &((unsigned char *)&dir)[2], 1);
			}
			write(fd, &((unsigned char *)&dir)[1], 1);
			write(fd, &((unsigned char *)&dir)[0], 1);
		}
		else if (check == 3)
		{
			ind = ft_atoi((*tmp)->arg[i]);
			write(fd, &((unsigned char *)&ind)[1], 1);
			write(fd, &((unsigned char *)&ind)[0], 1);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:28 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/08 10:41:10 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/*
 * print error message 
 */
t_bool	print_error(char *str, t_error error)
{
	ft_printf("%sERROR%s: ", RED, RESET);
	if (error == MALLOC_FAIL)
		ft_printf("malloc fail at %s\n",str);
	if (error == WRONG_NB)
		ft_printf("wrong input number for %s\n", str);
	return (FALSE);
}

/*
 * print help function
 */
void	print_help(char *file_path)
{
	ft_printf("%sName\n\t%s%s", BOLD, file_path, RESET);
	ft_printf(" - is a program that the progress of the battle and");
	ft_printf(" declare the winner champion after its completion\n\n");
	ft_printf("%sHELP\n\t%s%s NO INPUT - ", BOLD, file_path, RESET);
	ft_printf("print this help message\n\n");
	ft_printf("%sUsage\n\t%s%s [-d N | -n N]", BOLD, file_path, RESET);
	ft_printf(" <champion1.cor> <...>\n\n");
	ft_printf("%sFlag%s\n", BOLD, RESET);
	ft_printf("\t%s-d N%s\tDump memory (32 octets per line) after", BOLD, RESET);
	ft_printf(" %sN%s cycles and exit\n", BOLD, RESET);
	ft_printf("\t%s-n N%s\t", BOLD, RESET);
	ft_printf("Set %sN%s of the next player\n", BOLD, RESET);
}

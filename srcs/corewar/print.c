/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 14:59:28 by itkimura          #+#    #+#             */
/*   Updated: 2022/12/07 14:59:31 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/corewar.h"

/* print error message */
void print_error(char *str, t_error error)
{
	if (error == MALLOC_FAIL)
		ft_printf("ERROR: malloc fail at %s", str);
	// we will have more error mesage here
}

/*print help function*/
void print_help(void)
{

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:28:33 by leo               #+#    #+#             */
/*   Updated: 2022/12/11 04:03:59 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_exit(t_asmdata *data, char *str, bool is_error)
{
	if (is_error)
		ft_printf("[Error]: %s\n", str);
	/*
		need to free all structs inside of data struct.
		 hashtable
		 	-> name, next;
		labels
			-> name, next;
		oplist
			->instructions;
		header
	*/
	ft_memdel((void **)&data);
	exit (1);
}

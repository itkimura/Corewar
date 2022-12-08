/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:19 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 12:38:35 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(void)
{
	t_asmdata	*data;

	data = (t_asmdata *)malloc(sizeof(t_asmdata));
	if (!data)
		return (0);
	data->hashtable = NULL;
	if (!init_hashtable(data))
		free_exit(data);
	// print_hashtable(data);

	print_statement(g_statements[get_index(data, "live")]);
	// print_statement(tmp);
	ft_printf("Exit\n");
	return (0);
}

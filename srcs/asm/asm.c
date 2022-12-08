/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:56:19 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 14:55:57 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_structs(t_asmdata *data)
{
	if (!init_hashtable(data) || !init_labels(data))
		free_exit(data);
}

int	main(void)
{
	t_asmdata	*data;

	data = (t_asmdata *)malloc(sizeof(t_asmdata));
	if (!data)
		return (0);
	init_structs(data);
	insert_label(data, "Test", 0);
	print_hashlabel(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:28:33 by leo               #+#    #+#             */
/*   Updated: 2022/12/14 06:06:50 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_hashtable(t_asmdata *data)
{
	t_hashstatement	*tmp_current;
	t_hashstatement	*tmp_next;
	int				i;

	i = 0;
	while (i < HASHTABLESIZE)
	{
		if (!data->hashtable[i])
		{
			i++;
			continue ;
		}
		ft_strdel(&(data->hashtable[i]->name));
		tmp_current = data->hashtable[i]->next;
		while (tmp_current)
		{
			tmp_next = tmp_current->next;
			ft_strdel(&tmp_current->name);
			ft_memdel((void **)&tmp_current);
			tmp_current = tmp_next;
		}
		ft_memdel((void **)&data->hashtable[i]);
		i++;
	}
	ft_memdel((void **)&data->hashtable);
}

static void	free_labels(t_asmdata *data)
{
	t_labels	*tmp_current;
	t_labels	*tmp_next;
	int			i;

	i = 0;
	while (i < HASHTABLESIZE)
	{
		if (!data->labels[i])
		{
			i++;
			continue ;
		}
		ft_strdel(&(data->labels[i]->name));
		tmp_current = data->labels[i]->next;
		while (tmp_current)
		{
			tmp_next = tmp_current->next;
			ft_strdel(&tmp_current->name);
			ft_memdel((void **)&tmp_current);
			tmp_current = tmp_next;
		}
		ft_memdel((void **)&data->labels[i]);
		i++;
	}
	ft_memdel((void **)&data->labels);
}

static void	free_oplist(t_asmdata *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->opcount)
	{
		j = 0;
		ft_strdel(&data->oplist[i]->instruction);
		ft_strdel(&data->oplist[i]->statement);
		while (j < 3 && data->oplist[i]->arg[j])
			ft_strdel(&data->oplist[i]->arg[j++]);
		ft_memdel((void **)&data->oplist[i]);
		i++;
	}
	ft_memdel((void **)&data->oplist);
}

void	free_exit(t_asmdata *data, char *str, bool is_error)
{
	bool	leaks;

	leaks = data->leaks;
	if (is_error)
		ft_printf("[Error]: %s\n", str);
	free_labels(data);
	free_hashtable(data);
	free_oplist(data);
	ft_memdel((void **)&data->header);
	ft_memdel((void **)&data);
	if (leaks)
		system("leaks -q asm");
	exit (1);
}

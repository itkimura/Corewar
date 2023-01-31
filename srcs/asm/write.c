/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccariou <ccariou@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:43:57 by ccariou           #+#    #+#             */
/*   Updated: 2023/01/30 18:27:14 by ccariou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdlib.h>
/*
char	*make_champ_code(t_asmdata *data)
{
	printf("data->oplist[%d] == %s\n", index, data->oplist[1]->label);
//	to_hexa(data->oplist[i]->statement;
//	to_hexa(data->oplist[i]->arg_code);
//	to_hexa(data->oplist[i]->args);
	    while statement
         arg code
while(arg)
     t_op *tmp
int jump_to;
jump_to = 0;

get_label_adr(data, &tmp, arg[1])
jump_to = tmp.totalbyte - tmp.byte
}
*/

void	hex_translator(char *str, int fd, int len)
{
	int		i;
	int		temp;

	temp = 0;
	i = 0;
	while (i < len)
	{
		if (str[i])
			temp = (int)str[i];
		else
			temp = 0;
		write(fd, &temp, 1);
		i++;
	}
}
/*

void	to_bytecode(char *transcript,
							int i,
							int32_t value,
							int	size)
{
	int8_t		count;
	int			ret;

	i = 0;
	count = 0;
	while (i <= size)
	{
		ret = (uint8_t)((value >> count) & 0xFF);
		transcript[i + size - 1] = (uint8_t)((value >> count) & 0xFF);
		count  += 8;
		i++;
	}
}
*/

int	byte_shift_translate(int value)
{
	int	converted;

	converted = 0;
	converted |= ((0x000000ff & value) << 24);
	converted |= ((0x0000ff00 & value) << 8);
	converted |= ((0x00ff0000 & value) >> 8);
	converted |= ((0xff000000 & value) >> 24);
	return (converted);
}

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

char	*translate_labels(char *arg, int byte)
{
	char	*percent;

	if (arg && ft_strchr(arg, ':'))
	{
		if ((arg)[0] == '%')
		{
			percent = ft_strdup("%"),
			arg = ft_itoa(byte);
			percent = ft_strjoin(percent, arg);
			arg = percent;
		}
		else
			arg = ft_itoa(byte);
	}
	return(arg);
}
/*
 * statement
 * typecode
 * arg
 */
void	champ_code(t_op **data, int fd)
{
	int	i;
	int	j;
	int	dir;
	int	ind;
	int	check;
//	int	argcode;
	char	buf;
	t_op	**tmp;

	i = 0;
	j = 1;
	tmp = data;
	ft_printf("instruction == %s, table name == %s\n", (*tmp)->instruction, g_statements[j].name);//g_statements[HASHTABLESIZE]
	while (ft_strcmp((*tmp)->statement, g_statements[j].name) != 0)
	{
		j++;
		ft_printf("j == %d instruction == %s, table name == %s\n", j, (*tmp)->statement, g_statements[j].name);//g_statements[HASHTABLESIZE]
	}
	buf = g_statements[j].code;
	ft_printf("table name == %s\n", g_statements[j].name);//g_statements[HASHTABLESIZE]
	write(fd, &buf, 1);
	buf = '0';
	if (ft_strcmp((*tmp)->statement, g_statements[j].name) == 0)
	{
		buf = (*tmp)->argcode;
		ft_printf("buf == %c statement == %c\n", buf, g_statements[j].argcode);//g_statements[HASHTABLESIZE]
		write(fd, &buf, 1);
	}
	buf = '0';
	while(i < 3)
	{
		(*tmp)->arg[i] = translate_labels((*tmp)->arg[i], (*tmp)->byte);
		check = check_arg((*tmp)->arg[i]);
		ft_printf("check == %d fd == %d i == %d arg[%d] == %s\n", check, fd, i, i, (*tmp)->arg[i]);
		if (check == 1)
		{
			buf = ft_atoi(ft_strchr((*tmp)->arg[i], 'r') + 1);
			write(fd, &buf, 1);	
		}
		else if (check == 2)
		{
//			if (ft_strlen((*tmp)->arg[i]) > 2)
//				(long)(*tmp)->arg[i] |= 1L << 7;	
			dir = ft_atoi(&(*tmp)->arg[i][1]);
			ft_printf("dir == %d, arg[%d] == %d, char == %s\n", dir, i, ft_atoi(&(*tmp)->arg[i][1]), &(*tmp)->arg[i][1]);
		/*	if (!g_statements[i].size)
			{
				write(fd, &((unsigned char*)&dir)[3], 1);
				write(fd, &((unsigned char*)&dir)[2], 1);
			} */
			write(fd, &((unsigned char*)&dir)[1], 1);
			write(fd, &((unsigned char*)&dir)[0], 1);
		}
		else if (check == 3)
		{
			ind = ft_atoi((*tmp)->arg[i]);
			ft_printf("ind == %d\n", ind);
			write(fd, &((unsigned char*)&ind)[1], 1);
			write(fd, &((unsigned char*)&ind)[0], 1);
			ft_printf("teub de loup\n");
		}
		i++;
	}

//	get_label_adr(data, &tmp, arg[1])
//	get_label_adr(data, &tmp, arg[2])
//	get_label_adr(data, &tmp, arg[3])
}


void	write_to_file(t_asmdata *data)
{
//	int32_t	len;
	int32_t	helper;
	int		i;
	int		index;
	int		fd;
//	char	*transcript;
//	char	champ_code[256] = " sti r1, %:live, %1";
	fd = open("teub", O_RDWR | O_CREAT | O_TRUNC, 0600);
//	champ_code = make_champ_code(data);
//	champ = ft_strnew(ft_strlen(data->header->prog_name));
//	ft_memset((void *)data->header->prog_name, 0, PROG_NAME_LENGTH + 1);
	i = 0;
	index = 1;
//	len = 4 + 128 + 4 + 4 + COMMENT_LENGTH + 4 + ft_strlen(champ_code); //+ data->opsize;
	ft_printf("*need to translate : MAGIC, PROG NAME, NULL, LEN, COMMENT, NULL, CHAMPCODE\n");
	ft_printf("**********MAGIC_HEADER*********\n");
	helper = byte_shift_translate(COREWAR_EXEC_MAGIC);
	write(fd, &helper, 4);
	ft_printf("**********PROG_NAME + NULL + LEN*********\n");
	hex_translator(data->header->prog_name, fd, PROG_NAME_LENGTH);
	write(fd, NULL, 4);
	helper = byte_shift_translate(data->opsize);
	write(fd, &helper, 4);
//	ft_printf("champ == %d prog_name == %s\n", champ, data->header->prog_name);
	ft_printf("**********COMMENT*********\n");
	hex_translator(data->header->comment, fd, COMMENT_LENGTH);
	ft_printf("data->oplist[%d] == %s\n", index, data->oplist[0]->label);
//	ft_printf("champ == %d prog_name == %s\n", champ, data->header->prog_name);
//	ft_printf("data->opsize == %d\n", data->opsize);
//	transcript = ft_strnew(len);
	ft_printf("**********CHAMP_CODE*********\n");
	while(data->oplist[i])
	{
		ft_printf("arg == %d instruction == %s\n", data->oplist[i]->args, data->oplist[i]->instruction);
		champ_code(&data->oplist[i], fd);
		i++;
	}
	/*
	i += 4;
	i += 128;
	i += 4;
	i += 2052;
	*/
}

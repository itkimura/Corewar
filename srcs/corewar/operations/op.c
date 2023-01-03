/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:47:39 by thule             #+#    #+#             */
/*   Updated: 2023/01/02 11:53:16 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 
 * 1.statement name
 * 2.number of argument
 * 3.arugment
 * 4.statement code (index)
 * 5.cycle to dye
 * 6.argument code type (true or false)
 * 7.size of T_DIR
 * 8.pointer to function
 */
t_op	g_op_tab[16] =
{
	{"live",	1,	{T_DIR},												1,	10,		false,	4,	&op_live},
	{"ld",		2,	{T_DIR | T_IND, T_REG},									2,	5,		true,	4,	&op_ld},
	{"st",		2,	{T_REG, T_IND | T_REG},									3,	5,		true,	4,	&op_st},
	{"add",		3,	{T_REG, T_REG, T_REG},									4,	10,		true,	4,	&op_add},
	{"sub",		3,	{T_REG, T_REG, T_REG},									5,	10,		true,	4,	&op_sub},
	{"and",		3,	{T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},	6,	6,		true,	4,	&op_and},
	{"or",		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	7,	6,		true,	4,	&op_or},
	{"xor",		3,	{T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},	8,	6,		true,	4,	&op_xor},
	{"zjmp",	1,	{T_DIR},												9,	20,		false,	2,	&op_zjmp},
	{"ldi",		3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			10,	25,		true,	2,	&op_ldi},
	{"sti",		3,	{T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},			11,	25,		true,	2,	&op_sti},
	{"fork",	1,	{T_DIR},												12,	800,	false,	2,	&op_fork},
	{"lld",		2,	{T_DIR | T_IND, T_REG},									13,	10,		true,	4,	&op_lld},
	{"lldi",	3,	{T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},			14,	50,		true,	2,	&op_lldi},
	{"lfork",	1,	{T_DIR},												15,	1000,	false,	2,	&op_lfork},
	{"aff",		1,	{T_REG},												16,	2,		true,	4,	&op_aff}
};

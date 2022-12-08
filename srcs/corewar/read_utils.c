/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:36:07 by thle              #+#    #+#             */
/*   Updated: 2022/12/08 17:36:26 by thle             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	read_then_terminate_bytes(int fd, unsigned char *bytes, int size)
{
	read(fd, bytes, size);
	bytes[size] = '\0';
}

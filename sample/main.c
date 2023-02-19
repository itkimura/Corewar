/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 23:41:51 by leo               #+#    #+#             */
/*   Updated: 2022/11/21 00:47:24 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

# define PROG_NAME_LENGTH		(128)

int	main(int argc, char **argv)
{
	char a = 'B';
	char *str = "Batman";
	int i = 0;

	ft_printf("00ea 83f3 ");
	while (i < PROG_NAME_LENGTH + 4)
	{
		if (i < ft_strlen(str))
			ft_printf("%s", ft_itoa_base(str[i], 16, 0));
		else
			ft_printf("00");
		if ((i + 4) % 16 == 15)
			ft_printf("\n");
		else if (i % 2)
			ft_printf(" ");
		i++;
	}
}
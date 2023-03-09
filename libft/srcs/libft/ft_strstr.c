/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:21:24 by itkimura          #+#    #+#             */
/*   Updated: 2023/03/01 13:43:27 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	char	*str;

	if (!haystack)
		return (0);
	i = 0;
	j = 0;
	str = (char *)haystack;
	if (!*needle)
		return (str);
	while (str[i])
	{
		j = 0;
		while (str[i + j] && str[i + j] == needle[j])
		{
			if (!needle[j + 1])
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (0);
}

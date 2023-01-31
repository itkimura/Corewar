/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 13:26:36 by leotran           #+#    #+#             */
/*   Updated: 2022/02/28 10:54:45 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_update(char const *s1, char const *s2)
{
	char		*arr;
	char		*temp;
	int			i;
	size_t		len;

	i = 0;
	temp = (char *)s1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr)
	{
		while (*s1)
			arr[i++] = *s1++;
		ft_strdel(&temp);
		temp = (char *)s2;
		while (*s2)
			arr[i++] = *s2++;
		arr[i] = '\0';
		ft_strdel(&temp);
	}
	return (arr);
}

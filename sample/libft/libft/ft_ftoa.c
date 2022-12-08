/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:49:29 by leotran           #+#    #+#             */
/*   Updated: 2022/03/06 14:07:34 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	bankers_rounding(long double num, long double sign, char last_digit)
{
	int	rounding_num;
	int	res;

	rounding_num = last_digit - '0';
	res = 0;
	num = (num - (long long)num) * sign;
	if (num > 0.5)
		res++;
	else if (num == 0.5)
		res = ((rounding_num + 1 * (int)sign) % 2 == 0);
	return (res);
}

static char	*correct_rounding(char *int_num, char *fract_num, int i)
{
	long long	new_int;
	int			sign;

	sign = 1 - 2 * (*int_num == '-');
	fract_num[--i] = '0';
	while (i-- > 0 && fract_num[i] == '9')
		fract_num[i] = '0';
	if (i >= 0)
		fract_num[i] += 1;
	else
	{
		new_int = ft_atoi(int_num);
		ft_strdel(&int_num);
		int_num = ft_itoa_base(new_int + sign, 10, 0);
	}	
	return (int_num);
}

static char	*strjoin_int_fract(char *int_num, char *fract_num, int sign)
{
	char	*res;
	size_t	size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(int_num) + ft_strlen(fract_num) + 1 \
	+ (sign == -1 && *int_num == '0');
	res = ft_strnew(size);
	if (res)
	{
		if (sign == -1 && *int_num == '0')
			res[i++] = '-';
		while (int_num[j])
			res[i++] = int_num[j++];
		res[i++] = '.';
		j = 0;
		while (fract_num[j])
			res[i++] = fract_num[j++];
	}
	ft_strdel(&int_num);
	ft_strdel(&fract_num);
	return (res);
}

static char	*fract_to_a(char *int_num, long double num, int prec_flag, int prec)
{
	char		*fract_num;
	long double	sign;
	int			i;
	int			roundup;

	i = 0;
	sign = 1.0 - 2.0 * ((num < 0) || (1 / num < 0 && num == 0));
	num *= sign;
	if (prec_flag == 0)
		prec = 6;
	fract_num = ft_strnew(prec);
	while (prec-- > 0)
	{
		num *= 10;
		fract_num[i++] = ((long long)num % 10) + '0';
		num -= (long long)num;
	}
	roundup = bankers_rounding(num, 1, fract_num[i - 1]);
	if (roundup == 1 && fract_num[i - 1] == '9')
		int_num = correct_rounding(int_num, fract_num, i);
	else
		fract_num[i - 1] += roundup;
	return (strjoin_int_fract(int_num, fract_num, (int)sign));
}

char	*ft_ftoa(long double num, int precision_flag, int precision)
{
	char		*int_num;
	char		*res;
	long double	sign;
	long long	roundup;
	long long	last_digit;

	sign = 1.0 - 2.0 * (num < 0);
	if (precision_flag == 1 && precision == 0)
	{
		last_digit = (long long)num % 10;
		roundup = bankers_rounding(num, sign, last_digit + '0') * (int)sign;
		if (1 / num < 0 && num == 0)
		{
			int_num = ft_itoa_base(-1, 10, 0);
			int_num[1] = '0';
		}
		else
			int_num = ft_itoa_base((long long)num + roundup, 10, 0);
		return (int_num);
	}	
	int_num = ft_itoa_base((long long)num, 10, 0);
	res = fract_to_a(int_num, num, precision_flag, precision);
	return (res);
}

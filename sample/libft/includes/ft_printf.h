/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 08:25:53 by leo               #+#    #+#             */
/*   Updated: 2022/09/23 11:40:12 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONVERSION "cspdiouxXf%bn"
# define FLAGS 		"0# -+"
# define LENGTH 	"hhllLz"

# define DASH_HSP		22
# define HPS_ZD			9
# define ERROR_FLAG		5
# define PRECISION		1
# define WIDTH			0

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"
# include "ft_string_mod.h"

typedef enum e_flags
{
	ZERO = 1,
	HASH = 2,
	SPACE = 4,
	DASH = 8,
	PLUS = 16,
	FLAG_NULL = 0
}	t_flags;

typedef enum e_length
{
	H = 0,
	HH = 1,
	L = 2,
	LL = 3,
	UPPER_L = 4,
	Z = 5,
	LENGTH_NULL = 6,
}	t_length;

typedef struct s_formats
{
	u_int16_t		formatcombo;
	u_int16_t		uint_flag[3];
	va_list			args;
	char			*num;
	int				flag[2];
	int				width;
	int				precision;
	int				length;
	char			specifier;
	int				char_count;
}	t_formats;

char	*get_flag(char *format, t_formats *mod);
char	*get_length(char *format, t_formats *mod);
char	*get_width(char *format, t_formats *mod, int flag);
char	*color_printf(char *format);

int		get_specifier(t_formats *mod, char c);
int		ft_printf(const char *format, ...);
int		get_formatcombo(t_formats *mod);

void	get_signed_type(t_formats *mod);
void	get_unsigned_type(t_formats *mod, int base, int flag);
void	plus_print(t_formats *mod);
void	hash_print(t_formats *mod);
void	zero_print(t_formats *mod);
void	space_print(t_formats *mod);
void	dash_print(t_formats *mod);
void	error_print(t_formats *mod);
void	precision_print(t_formats *mod);
void	get_format_lengths(t_formats *mod);
void	get_float_format_lengths(t_formats *mod);
void	width_print(t_formats *mod);
void	char_print(t_formats *mod);
void	str_print(t_formats *mod);
void	memaddr_print(t_formats *mod);
void	int_print(t_formats *mod);
void	base_uint_printf(t_formats *mod);
void	uint_print(t_formats *mod);
void	percentage_putchar(t_formats *mod);
void	custom_putstr(t_formats *mod);
void	float_printf(t_formats *mod);
void	asterisk_flag(t_formats *mod, int flag);
void	binary_printf(t_formats *mod);
void	n_conversion_printf(t_formats *mod);
void	reset_t_formats(t_formats *mod, int flag);
void	get_formats(char *format, t_formats *mod);

typedef void				(*t_printf)(t_formats *mod);
typedef void				(*t_flagprint)(t_formats *mod);

static const t_printf		g_printf[15] = {
	char_print,
	str_print,
	memaddr_print,
	int_print,
	base_uint_printf,
	uint_print,
	float_printf,
	percentage_putchar,
	binary_printf,
	n_conversion_printf
};

static const t_flagprint	g_flagprint[6] = {
	zero_print,
	hash_print,
	space_print,
	dash_print,
	plus_print,
	error_print
};

static const int			g_conversion[20] = {
	0,
	1,
	2,
	3,
	3,
	4,
	5,
	4,
	4,
	6,
	7,
	8,
	9,
	-1
};

static const char			*g_colors[] = {
	"BLK",
	"RED",
	"GRN",
	"YEL",
	"BLU",
	"MAG",
	"CYN",
	"WHT",
	"EOC"
};

#endif

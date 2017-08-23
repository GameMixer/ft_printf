/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:43:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 20:07:54 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "get_next_line.h"
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>

# define SPECS 18
# define IS_X(x) (x == 'X' || x == 'x')
# define IS_O(o) (o == 'O' || o == 'o')
# define IS_D(d) (d == 'D' || d == 'd')
# define IS_U(u) (u == 'U' || u == 'u')
# define ISXO(x) ((IS_X(x)) || (IS_O(x)))
# define ISLENMOD(m) (m == 'h' || m == 'l' || m == 'j' || m == 'z')

typedef enum	e_lenmod
{
	hh,
	h,
	l,
	ll,
	j,
	z
}				t_lenmod;

typedef enum	e_flag
{
	LFT = 1 << 0,
	POS = 1 << 1,
	INV = 1 << 2,
	ZER = 1 << 3,
	HTG = 1 << 4
}				t_flag;

typedef struct	s_vector
{
	size_t		len;
	size_t		cap;
	char		*data;
}				t_vector;

typedef struct	s_info
{
	char		flags;
	char		length;
	char		spec;
	int			width;
	int			prec;
	int			pset;
}				t_info;

typedef struct	s_convspec
{
	char		spec;
	void		(*ptr)(t_vector *, t_info *, va_list);
}				t_cspec;

/*
**	Where the main function is of this whole project
**		ft_printf.c
*/
int				ft_printf(const char *format, ...);
int				pf_vasprintf(char **ret, const char *format, va_list arg);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_snprintf(char *str, size_t size, const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);

/*
**	Handles the specifiers
**		spec_handle.c
*/
int				pf_strprintf(char **ret, const char *format, va_list arg);
void			pf_info_init(t_info *pfinfo);
void			pf_get_conv(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_conv_percent(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_handle_spec(t_vector *vector, const char **format,
					t_info *pfinfo, va_list arg);

/*
**	Check the format, see if it's valid
**		check.c
*/
int				pf_check_flags(const char **format, t_info *pfinfo);
int				pf_check_width(const char **format,
					t_info *pfinfo, va_list arg);
int				pf_check_prec(const char **format, t_info *pfinfo, va_list arg);
int				pf_check_len(const char **format, t_info *pfinfo);

/*
**	Handles the precision
**		prec_handle.c
*/
void			pf_prec_nums(t_info *pfinfo, char **str);
void			pf_prec_handle(t_info *pfinfo, char **str);
void			pf_pad_handle(t_info *pfinfo, char **str);
void			pf_prec_right(t_info *pfinfo, char **str, char *newstr);

/*
**	Handles the conversion into int/hex/octal
**		num_conv.c
*/
void			pf_conv_num(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_conv_octal(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_conv_hex(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_conv_uns(t_vector *vector, t_info *pfinfo, va_list arg);
intmax_t		pf_int_len(char length, va_list arg);

/*
**	Handles the conversion of strings
**		str_conv.c
*/
void			pf_conv_str(t_vector *vector, t_info *pfinfo, va_list arg);
char			*pf_null_str(t_info *pfinfo);

/*
**	Handles the conversions of wstrings, or wchar arrays.
**		wstr_conv.c
*/
void			pf_conv_wstr(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_prec_wstr(t_info *pfinfo, wchar_t *str);
char			*pf_wstr_to_str(wchar_t *wstr);
wchar_t			*pf_wstrdup(wchar_t *str);
size_t			pf_wstrlen(wchar_t *str);

/*
**	Handles the conversions of chars
**		char_conv.c
*/
void			pf_conv_char(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_null_char(t_vector *vector, char *str);
void			pf_conv_unicode(wchar_t wc, char *str);
int				pf_handle_wchar(char **str, va_list arg);
int				pf_unicode(wchar_t wc);

/*
**	Handles altering the conversions based on extra rules
**		xou_conv.c
*/
void			pf_xou_handle(char **str, t_info *pfinfo);
void			pf_alt_handle(t_info *pfinfo, char **str);
void			pf_x_toupper(char *str, char spec);
uintmax_t		pf_xou_len(char length, va_list arg);

/*
**	Handles various different conversions for extra credit
**	...honestly though the main thing I wanted was color...
**		bonus.c
*/
int				pf_colors(t_vector *vector, const char **format);
void			pf_conv_binary(t_vector *vector, t_info *pfinfo, va_list arg);
void			pf_conv_none(t_vector *vector, t_info *pfinfo, va_list arg);
intmax_t		*pf_none_len(t_info *pfinfo, va_list arg);

/*
**	Was going to handle floats, but not feeling like doing it.
**	So its just sitting here doing nothing.
**		float_conv.c
*/
void			pf_conv_float(t_vector *vector, t_info *pfinfo, va_list arg);

/*
**	Handles vectors...that's basically it...don't know what more you want
**		vector.c
*/
int				pf_vector_init(t_vector *vector, size_t cap);
void			pf_vector_clear(t_vector *vector);
void			pf_vector_push(t_vector *vector, char *data);
void			pf_vector_npush(t_vector *vector, char *data, size_t n);
void			pf_vector_resize(t_vector *vector, size_t min);

/*
**	Tools used that libft wouldnt be able to take care of in this case
**	Or maybe they would, and I'm just too lazy to put them into libft
**		util.c
*/
size_t			pf_findchar(const char *s, int c);
void			*pf_realloc(void *ptr, size_t src_size, size_t new_size);
void			pf_insert_to_str(char **s1, char *s2);
char			*pf_imaxtoa(intmax_t value);
char			*pf_uimaxtoa_base(uintmax_t value, int base, const char *str);

#endif

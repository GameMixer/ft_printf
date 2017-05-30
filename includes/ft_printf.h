/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:43:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 13:08:08 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "get_next_line.h"
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>

# define PRINTF_BUFF 32

char			g_buff[PRINTF_BUFF];
int				g_i;

/*
**		| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
**		|pre|wid| # | 0 | - | + |   | hh| h | ll|  l |  j |  z |
*/

typedef struct	s_flag
{
	int			ret;
	char		*frmt;
	int			index;
	char		spec;
	char		*arg;
	wchar_t		*warg;
	char		sign;
	va_list		vlst;
	int			type[13];
}				t_flag;

typedef struct	s_spec
{
	char		c;
	int			(*ptr)();
}				t_spec;

/*
**	Main part of the program. The whole reason Im doing this shit...
**		ft_printf.c
*/
int				ft_printf(const char *format, ...);
void			pf_end(t_flag *f);

/*
**	Stores output into a buffer
**		buff.c
*/
void			pf_buff_set(void);
void			pf_buff_display(t_flag *f);
void			pf_buff_null(t_flag *f);
void			pf_buff(char c, t_flag *f);

/*
**	Check the flags, see if they are valid
**		check.c
*/
int				pf_check(t_flag *f);
void			pf_check_flag(t_flag *f);
void			pf_check_width(t_flag *f);
void			pf_check_precision(t_flag *f);
void			pf_check_modifier(t_flag *f);

/*
**	Sets up the spec values and everything needed to output the data
**		init.c
*/
int				pf_init_validate(t_flag *f, va_list *args);
void			pf_initialize(t_flag *f);
void			pf_init_specs(t_spec *specs);
void			pf_init_specs_p2(t_spec *specs);

/*
**	Handles c flags
**		c_flag.c
*/
int				pf_modifier_c(t_flag *f, va_list *arg);
int				pf_handler_c(t_flag *f, va_list *arg);
int				pf_handler_wc(t_flag *f, va_list *arg);

/*
**	Handles d flags
**		d_flag.c
*/
char			*pf_modifier_d(t_flag *f, va_list *arg);
int				pf_handler_d(t_flag *f, va_list *arg);
int				pf_handler_wd(t_flag *f, va_list *arg);

/*
**	Handles p flag and undefined
**		p_flag_undefined.c
*/
int				pf_handler_p(t_flag *f, va_list *arg);
int				pf_handler_undefined(t_flag *f);

/*
**	Handles s flags
**		s_flag.c
*/
int				pf_handler_s(t_flag *f, va_list *arg);
int				pf_handler_ws(t_flag *f, va_list *arg);

/*
**	Handles u flag and o flag
**		u_o_flag.c
*/
char			*pf_modifier_u_o(t_flag *f, va_list *arg);
int				pf_handler_u(t_flag *f, va_list *arg);
int				pf_handler_o(t_flag *f, va_list *arg);

/*
**	Handles U flag and O flag
**		wu_wo_flag.c
*/
char			*pf_modifier_wu_wo(t_flag *f, va_list *arg);
int				pf_handler_wu(t_flag *f, va_list *arg);
int				pf_handler_wo(t_flag *f, va_list *arg);

/*
**	Handles x flags
**		x_flags.c
*/
char			*pf_modifier_x(t_flag *f, va_list *arg);
int				pf_handler_x(t_flag *f, va_list *arg);
int				pf_handler_wx(t_flag *f, va_list *arg);

/*
**	Handles what to do with which type of value
**		handle_format.c
*/
void			pf_apply_mask(t_flag *f, int *mask);
int				pf_handler_char(t_flag *f);
int				pf_handler_num(t_flag *f);

/*
**	Manages string values
**		display_char.c
*/
void			pf_display_arg(t_flag *f);
void			pf_zero_char(t_flag *f);
void			pf_minus_char(t_flag *f);
void			pf_width_char(t_flag *f);

/*
**	Manages numeric values
**		display_num.c
*/
void			pf_precision_without_width(t_flag *f);
void			pf_precision_num(t_flag *f, int len_zero);
void			pf_zero_num(t_flag *f);
void			pf_minus_num(t_flag *f);
void			pf_width_num(t_flag *f);

/*
**	Turns wchar array into a char array, which we can all understand...maybe
**		wchar_to_char.c
*/
char			*pf_wchar_to_char(wchar_t *ws);
int				pf_putwchar_in_char(wchar_t wchar, char *str, int i);

/*
**	Applys the flags to the argument
**		apply_flags.c
*/
void			pf_precision_string(t_flag *f);
void			pf_sharp(t_flag *f);
void			pf_space_plus_sharp(t_flag *f);

/*
**	Tools used that libft wouldnt be able to take care of in this case
**		util.c
*/
uintmax_t		pf_sign(t_flag *f, intmax_t nbr);
char			*pf_itoa_base(uintmax_t nbr, int base);
size_t			pf_wstrlen(wchar_t *ws);
int				pf_wcharlen(wchar_t wchar);
size_t			pf_wbytelen(wchar_t *ws);
char			*pf_wstrsub(wchar_t *ws, unsigned int start, size_t len);

#endif

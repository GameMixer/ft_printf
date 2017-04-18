/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:43:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/04/18 14:08:49 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "get_next_line.h"
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>

typedef struct	s_flag
{
	int			ret;
	char		*frmt;
	int			index;
	char		spec;
	int			type[13];
}				t_flag;

typedef struct	s_spec
{
	char		c;
	int			(*ptr)();
}				t_spec;

int				ft_printf(const char *format, ...);

/*
**	Check the flags, see if they are valid
**		check.c
*/
int				pf_check(t_flag *f);
void			pf_check_flag(t_flag *f);
void			pf_check_width(t_flag *f);
void			pf_check_precision(t_flag *f);
void			pf_check_modifier(t_flag *f);

#endif

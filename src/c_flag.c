/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 15:24:42 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 11:14:04 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_modifier_c(t_flag *f, va_list *arg)
{
	wchar_t	wc;
	wchar_t	ws[2];

	wc = va_arg(*arg, wchar_t);
	ws[0] = wc;
	ws[1] = '\0';
	f->warg = ws;
	pf_handler_char(f);
	return (0);
}

int		pf_handler_c(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2};
	char		c;
	char		s[2];

	pf_apply_mask(f, mask);
	if (f->type[10] == 1)
		return (pf_modifier_c(f, arg));
	else
	{
		c = (char)va_arg(*arg, int);
		if (c == 0 && f->type[0] == -1)
			f->type[0] = 0;
		s[0] = c;
		s[1] = '\0';
		f->arg = s;
		pf_handler_char(f);
	}
	if (f->arg[0] == 0)
		pf_buff('\0', f);
	return (0);
}

int		pf_handler_wc(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2};

	pf_apply_mask(f, mask);
	return (pf_modifier_c(f, arg));
}

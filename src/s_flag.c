/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:18:42 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 11:15:14 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_handler_s(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2};

	pf_apply_mask(f, mask);
	if (f->type[10] == 1)
	{
		f->warg = va_arg(*arg, wchar_t *);
		pf_handler_char(f);
		return (0);
	}
	else
		f->arg = va_arg(*arg, char *);
	if (f->arg == 0)
		f->arg = "(null)";
	pf_handler_char(f);
	return (0);
}

int		pf_handler_ws(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2};

	pf_apply_mask(f, mask);
	f->warg = va_arg(*arg, wchar_t *);
	pf_handler_char(f);
	return (0);
}

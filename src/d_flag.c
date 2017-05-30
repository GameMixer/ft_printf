/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:05:30 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/18 16:50:00 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_modifier_d(t_flag *f, va_list *arg)
{
	intmax_t	data;
	uintmax_t	data_max;

	data = 0;
	if (f->type[12] == 1)
		data = (intmax_t)(va_arg(*arg, ssize_t));
	else if (f->type[11] == 1)
		data = (va_arg(*arg, intmax_t));
	else if (f->type[9] == 1)
		data = (intmax_t)(va_arg(*arg, long long));
	else if (f->type[10] == 1)
		data = (intmax_t)(va_arg(*arg, long));
	else if (f->type[8] == 1)
		data = (intmax_t)((short)va_arg(*arg, int));
	else if (f->type[7] == 1)
		data = (intmax_t)((char)va_arg(*arg, int));
	else if (f->spec == 'D')
		data = (intmax_t)(va_arg(*arg, long));
	else if (f->spec == 'd' || f->spec == 'i')
		data = (intmax_t)(va_arg(*arg, int));
	data_max = pf_sign(f, data);
	return (pf_itoa_base(data_max, 10));
}

int		pf_handler_d(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	pf_apply_mask(f, mask);
	f->arg = pf_modifier_d(f, arg);
	pf_handler_num(f);
	return (0);
}

int		pf_handler_wd(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1};

	pf_apply_mask(f, mask);
	f->arg = pf_modifier_d(f, arg);
	pf_handler_num(f);
	return (0);
}

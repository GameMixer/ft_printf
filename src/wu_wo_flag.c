/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_wo_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 16:11:02 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 16:18:45 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_modifier_wu_wo(t_flag *f, va_list *arg)
{
	intmax_t	data;

	if (f->type[12] == 1)
		data = (uintmax_t)(va_arg(*arg, size_t));
	else if (f->type[11] == 1)
		data = (va_arg(*arg, uintmax_t));
	else if (f->type[9] == 1)
		data = (uintmax_t)(va_arg(*arg, unsigned long long));
	else if (f->type[10] == 1)
		data = (uintmax_t)(va_arg(*arg, unsigned long));
	else if (f->type[8] == 1)
		data = (uintmax_t)(va_arg(*arg, unsigned int));
	else if (f->type[7] == 1)
		data = (uintmax_t)(va_arg(*arg, unsigned int));
	else
		data = (uintmax_t)(va_arg(*arg, unsigned long));
	if (f->spec == 'U')
		return (pf_itoa_base(data, 10));
	if (f->spec == 'O')
		return (pf_itoa_base(data, 8));
	return (NULL);
}

int		pf_handler_wu(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1};

	pf_apply_mask(f, mask);
	f->arg = pf_modifier_wu_wo(f, arg);
	pf_handler_num(f);
	return (0);
}

int		pf_handler_wo(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	pf_apply_mask(f, mask);
	f->arg = pf_modifier_wu_wo(f, arg);
	if (f->type[0] == -1 && f->arg[0] != '0' && f->type[2] == 1)
		f->type[0] = 0;
	pf_handler_num(f);
	return (0);
}

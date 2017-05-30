/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_flag_undefined.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 16:01:29 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 16:10:00 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_handler_p(t_flag *f, va_list *arg)
{
	static int	mask[13] = {0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2};

	f->type[2] = 1;
	pf_apply_mask(f, mask);
	f->arg = ft_strtolower(pf_itoa_base((uintmax_t)va_arg(*arg, void *), 16));
	if (f->type[0] == -1 && f->arg[0] == '0')
	{
		pf_buff('0', f);
		pf_buff('x', f);
	}
	else
		pf_handler_num(f);
	return (0);
}

int		pf_handler_undefined(t_flag *f)
{
	static int	mask[13] = {0, 0, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 2};
	char		c[2];

	f->type[0] = 0;
	if (f->spec == 0)
	{
		f->ret = 0;
		return (f->ret);
	}
	c[0] = f->spec;
	c[1] = '\0';
	f->arg = c;
	pf_apply_mask(f, mask);
	return (pf_handler_char(f));
}

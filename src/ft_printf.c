/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:39:17 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 14:10:48 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_end(t_flag *f)
{
	if (f->type[0] >= 0 && f->arg && f->arg[0] != '\0' && f->arg[0] != '0')
	{
		if (f->spec == 'x' || f->spec == 'X' || f->spec == 'o' ||
				f->spec == 'O' || f->spec == 'u' || f->spec == 'U' ||
				f->spec == 'd' || f->spec == 'D' || f->spec == 'p' ||
				f->spec == 'S' || f->spec == 'i' || (f->spec == 's' &&
					f->type[0] < (int)ft_strlen(f->arg) && f->type[0] > 0) ||
				f->spec == 'C' || (f->spec == 'c' && f->type[10] == 1))
			free(f->arg);
	}
}

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_flag	f;
	int		i;

	va_start(args, format);
	i = -1;
	f.ret = 0;
	pf_buff_set();
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			f.frmt = (char *)&format[++i];
			if (pf_init_validate(&f, &args) == -1)
				break ;
			i += f.index;
		}
		else if (format[i] != '\0' && format[i] != '%')
			pf_buff(format[i], &f);
	}
	if (g_i > 0)
		pf_buff_display(&f);
	va_end(args);
	return (f.ret);
}

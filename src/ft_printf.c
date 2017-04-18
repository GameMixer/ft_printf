/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:39:17 by gderenzi          #+#    #+#             */
/*   Updated: 2017/04/17 18:10:09 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	args;
	t_flag	f;
	int		i;

	if (!format)
	{
		ft_putstr("ft_printf: format string must be valid\n");
		exit(1);
	}
	va_start(args, format);
	i = 0;
	f.ret = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			
		}
		i += f.index;
	}
	va_end(args);
	return (f.ret);
}

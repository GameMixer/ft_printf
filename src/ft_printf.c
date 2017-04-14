/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:39:17 by gderenzi          #+#    #+#             */
/*   Updated: 2017/04/06 16:35:39 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	args;
	int		ret;

	if (!format)
	{
		ft_putstr("ft_printf: format string must be valid\n");
		exit(1);
	}
	va_start(args, format);
	ret = handle_format(format, args);
	va_end(args);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:39:17 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:52:21 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;
	char	*ret;

	if (!format || !*format)
		return (0);
	va_start(arg, format);
	len = pf_vasprintf(&ret, format, arg);
	write(1, ret, len);
	free(ret);
	va_end(arg);
	return (len);
}

int		pf_vasprintf(char **ret, const char *format, va_list arg)
{
	if (*format == '\0')
		*ret = ft_strnew(0);
	if (!ret || !format || !*format)
		return (0);
	if (ft_strchr(format, '%') == NULL)
	{
		if ((*ret = ft_strdup(format)) == NULL)
			return (-1);
		return (ft_strlen(*ret));
	}
	return (pf_strprintf(ret, format, arg));
}

int		ft_sprintf(char *str, const char *format, ...)
{
	va_list	arg;
	int		len;
	char	*ret;

	if (!str || !format)
		return (0);
	va_start(arg, format);
	len = pf_vasprintf(&ret, format, arg);
	ft_strcpy(str, ret);
	free(ret);
	va_end(arg);
	return (len);
}

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	arg;
	int		len;
	char	*ret;

	if (!str || !format)
		return (0);
	va_start(arg, format);
	len = pf_vasprintf(&ret, format, arg);
	if (size == 0)
		return (len);
	else if (size - 1 == 0)
		str[0] = '\0';
	ft_strncpy(str, ret, size - 1);
	free(ret);
	va_end(arg);
	return (len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	arg;
	int		len;
	char	*ret;

	if (!format || !*format || fd < 0)
		return (0);
	va_start(arg, format);
	len = pf_vasprintf(&ret, format, arg);
	write(fd, ret, len);
	free(ret);
	va_end(arg);
	return (len);
}

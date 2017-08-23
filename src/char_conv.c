/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:42:33 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 18:47:17 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_conv_unicode(wchar_t wc, char *str)
{
	if (wc < (MB_CUR_MAX == 1 ? 0xFF : 0x7F))
		str[0] = (unsigned char)wc;
	else if (wc < (1 << 11))
	{
		str[0] = (unsigned char)((wc >> 6) | 0xC0);
		str[1] = (unsigned char)((wc & 0x3F) | 0x80);
	}
	else if (wc < (1 << 16))
	{
		str[0] = (unsigned char)(((wc >> 12)) | 0xE0);
		str[1] = (unsigned char)(((wc >> 6) & 0x3F) | 0x80);
		str[2] = (unsigned char)((wc & 0x3F) | 0x80);
	}
	else if (wc < (1 << 21))
	{
		str[0] = (unsigned char)(((wc >> 18)) | 0xF0);
		str[1] = (unsigned char)(((wc >> 12) & 0x3F) | 0x80);
		str[2] = (unsigned char)(((wc >> 6) & 0x3F) | 0x80);
		str[3] = (unsigned char)((wc & 0x3F) | 0x80);
	}
}

int		pf_unicode(wchar_t wc)
{
	if (wc < (1 << 7))
		return (1);
	else if (wc < (1 << 11))
		return (2);
	else if (wc < (1 << 16))
		return (3);
	else if (wc < (1 << 21))
		return (4);
	return (0);
}

int		pf_handle_wchar(char **str, va_list arg)
{
	wchar_t	wc;
	int		len;

	wc = va_arg(arg, wchar_t);
	len = pf_unicode(wc);
	*str = ft_strnew(len);
	pf_conv_unicode(wc, *str);
	return (wc == '\0');
}

void	pf_conv_char(t_vector *vector, t_info *pfinfo, va_list arg)
{
	char	c;
	char	*str;
	int		null;

	if (pfinfo->spec == 'C' || pfinfo->length == l)
	{
		null = pf_handle_wchar(&str, arg);
		if (null)
			str[0] = null;
	}
	else
	{
		c = va_arg(arg, int);
		str = ft_strnew(1);
		null = (c == '\0') ? 1 : 0;
		str[0] = c + null;
	}
	pf_pad_handle(pfinfo, &str);
	if (null)
		pf_null_char(vector, str);
	else
		pf_vector_push(vector, str);
	free(str);
}

void	pf_null_char(t_vector *vector, char *str)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == 1)
			str[i] = 0;
		i++;
	}
	pf_vector_npush(vector, str, len);
}

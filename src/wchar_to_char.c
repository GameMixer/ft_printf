/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_to_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:38:37 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 17:58:37 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_putwchar_in_char(wchar_t wchar, char *str, int i)
{
	int	size;

	size = pf_wcharlen(wchar);
	if (size == 1)
		str[i++] = wchar;
	else if (size == 2)
	{
		str[i++] = (wchar >> 6) + 0xC0;
		str[i++] = (wchar & 0x3F) + 0x80;
	}
	else if (size == 3)
	{
		str[i++] = (wchar >> 12) + 0xE0;
		str[i++] = ((wchar >> 6) & 0x3F) + 0x80;
		str[i++] = (wchar & 0x3F) + 0x80;
	}
	else
	{
		str[i++] = (wchar >> 18) + 0xF0;
		str[i++] = ((wchar >> 12) & 0x3F) + 0x80;
		str[i++] = ((wchar >> 6) & 0x3F) + 0x80;
		str[i++] = (wchar & 0x3F) + 0x80;
	}
	return (i);
}

char	*pf_wchar_to_char(wchar_t *ws)
{
	char	*str;
	int		i;
	int		k;
	int		len;

	if (!ws)
		return (0);
	i = 0;
	k = 0;
	len = pf_wbytelen(ws);
	str = (char *)malloc(sizeof(char) * len);
	str[len] = '\0';
	while (ws[k])
	{
		i = pf_putwchar_in_char(ws[k], str, i);
		k++;
	}
	return (str);
}

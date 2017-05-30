/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:28:40 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 17:46:42 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	pf_sign(t_flag *f, intmax_t nbr)
{
	f->sign = '+';
	if (nbr < 0)
	{
		f->sign = '-';
		nbr = -nbr;
	}
	return ((uintmax_t)nbr);
}

char		*pf_itoa_base(uintmax_t nbr, int base)
{
	intmax_t	i;
	uintmax_t	n;
	int			n_arr[64];
	char		*result;

	if (nbr == 0)
		return ("0");
	i = 0;
	n = (intmax_t)nbr;
	while (n > 0)
	{
		n_arr[i++] = n % base;
		n /= base;
	}
	result = (char *)malloc(sizeof(char) * --i);
	result[i + 1] = '\0';
	while (i >= 0)
		result[n++] = HEXB_UP[n_arr[i--]];
	return (result);
}

size_t		pf_wstrlen(wchar_t *ws)
{
	size_t	len;

	len = 0;
	if (!ws)
		return (0);
	while (*(ws++))
		len++;
	return (len);
}

int			pf_wcharlen(wchar_t wchar)
{
	if (wchar <= 0x7F)
		return (1);
	else if (wchar <= 0x7FF)
		return (2);
	else if (wchar <= 0xFFFF)
		return (3);
	return (4);
}

size_t		pf_wbytelen(wchar_t *ws)
{
	size_t	len;
	size_t	bytelen;

	len = pf_wstrlen(ws);
	bytelen = 0;
	while (len > 0)
	{
		bytelen += pf_wcharlen(*ws);
		ws++;
		len--;
	}
	return (bytelen);
}

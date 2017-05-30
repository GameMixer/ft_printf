/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:04:38 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 18:10:42 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_wstrsub(wchar_t *ws, unsigned int start, size_t len)
{
	int		real_len;
	int		i;
	char	*str;

	real_len = 0;
	i = 0;
	while (ws[i] != '\0' && (int)len >= pf_wcharlen(ws[i]))
	{
		len -= pf_wcharlen(ws[i]);
		real_len += pf_wcharlen(ws[i]);
		i++;
	}
	str = pf_wchar_to_char(ws);
	return (ft_strsub(str, start, real_len));
}

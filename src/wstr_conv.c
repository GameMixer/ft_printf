/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 17:38:37 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:46:36 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*pf_wstrdup(wchar_t *str)
{
	wchar_t	*res;
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	res = (wchar_t *)malloc(sizeof(wchar_t) * (size + 1));
	if (!res)
		return (NULL);
	size = 0;
	while (str[size])
	{
		res[size] = str[size];
		size++;
	}
	res[size] = '\0';
	return (res);
}

size_t	pf_wstrlen(wchar_t *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		count += pf_unicode(str[i]);
		i++;
	}
	return (count);
}

void	pf_prec_wstr(t_info *pfinfo, wchar_t *str)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	if (pfinfo->prec == -1)
		return ;
	if (pf_wstrlen(str) <= (size_t)pfinfo->prec)
		return ;
	while (str[i] && count <= (size_t)pfinfo->prec)
	{
		count += pf_unicode(str[i]);
		i++;
	}
	str[i - 1] = '\0';
}

char	*pf_wstr_to_str(wchar_t *wstr)
{
	char	*ret;
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	ret = ft_strnew(pf_wstrlen(wstr));
	while (wstr[i])
	{
		pf_conv_unicode(wstr[i], ret + pos);
		pos += pf_unicode(wstr[i]);
		i++;
	}
	return (ret);
}

void	pf_conv_wstr(t_vector *vector, t_info *pfinfo, va_list arg)
{
	wchar_t	*wtemp;
	char	*str;

	wtemp = va_arg(arg, wchar_t *);
	if (!wtemp)
		str = pf_null_str(pfinfo);
	else
	{
		wtemp = pf_wstrdup(wtemp);
		pf_prec_wstr(pfinfo, wtemp);
		str = pf_wstr_to_str(wtemp);
		free(wtemp);
	}
	pf_pad_handle(pfinfo, &str);
	pf_vector_push(vector, str);
	free(str);
}

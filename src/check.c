/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:46:20 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:44:54 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_check_flags(const char **format, t_info *pfinfo)
{
	const char	flags[] = "-+ 0#";
	size_t		i;

	i = 0;
	while (flags[i] != **format && flags[i])
		i++;
	if (flags[i])
	{
		pfinfo->flags = pfinfo->flags | (1 << i);
		(*format)++;
		return (1);
	}
	return (0);
}

int		pf_check_width(const char **format, t_info *pfinfo, va_list arg)
{
	int		res;

	res = 0;
	if (**format == '*')
	{
		pfinfo->width = va_arg(arg, int);
		if (pfinfo->width < 0)
		{
			if (!(pfinfo->flags & LFT))
				pfinfo->flags ^= LFT;
			pfinfo->width = pfinfo->width * -1;
		}
		(*format)++;
		return (1);
	}
	if (!(ft_isdigit(**format)))
		return (0);
	while (ft_isdigit(**format))
	{
		res = res * 10 + (**format - '0');
		(*format)++;
	}
	pfinfo->width = res;
	return (1);
}

int		pf_check_prec(const char **format, t_info *pfinfo, va_list arg)
{
	int		res;

	res = 0;
	if (**format != '.')
		return (0);
	pfinfo->pset = 1;
	(*format)++;
	if (**format == '*')
	{
		pfinfo->prec = va_arg(arg, int);
		if (pfinfo->prec < -1)
			pfinfo->prec = -1;
		(*format)++;
		return (1);
	}
	while (ft_isdigit(**format))
	{
		res = res * 10 + (**format - '0');
		(*format)++;
	}
	pfinfo->prec = res;
	return (1);
}

int		pf_check_len(const char **format, t_info *pfinfo)
{
	const char	lengths[] = "hhlljz";
	int			i;

	i = 0;
	if (ISLENMOD(**format))
	{
		i = pf_findchar(lengths, **format);
		if (i == 0)
		{
			if (*(*format + 1) == 'h')
				++*format;
			else
				i = 1;
		}
		if (i == 2)
			i = (*(*format + 1) == 'l') ? 3 : 2;
		pfinfo->length = ft_max(i, pfinfo->length);
		++*format;
		return (1);
	}
	return (0);
}

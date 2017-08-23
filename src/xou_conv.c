/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xou_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 16:11:02 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:53:49 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

uintmax_t	pf_xou_len(char length, va_list arg)
{
	if (length == hh)
		return ((unsigned char)va_arg(arg, int));
	if (length == h)
		return ((unsigned short)va_arg(arg, int));
	if (length == l)
		return (va_arg(arg, unsigned long));
	if (length == ll)
		return (va_arg(arg, unsigned long long));
	if (length == j)
		return (va_arg(arg, uintmax_t));
	if (length == z)
		return (va_arg(arg, size_t));
	return (va_arg(arg, unsigned int));
}

void		pf_xou_handle(char **str, t_info *pfinfo)
{
	if (pfinfo->flags & ZER && pfinfo->prec == 0)
		pfinfo->flags ^= ZER;
	if (pfinfo->prec == 0 && !ft_strcmp(*str, "0"))
		**str = '\0';
	pf_prec_nums(pfinfo, str);
	if (pfinfo->flags & ZER && pfinfo->spec == 'p')
	{
		pfinfo->width = ft_max(pfinfo->width - 2, 0);
		pf_pad_handle(pfinfo, str);
	}
	else if (pfinfo->flags & ZER && pfinfo->flags & HTG && (IS_X(pfinfo->spec)
				|| pfinfo->spec == 'b'))
	{
		pfinfo->width = ft_max(pfinfo->width - 2, 0);
		pf_pad_handle(pfinfo, str);
	}
	pf_alt_handle(pfinfo, str);
	if (!(pfinfo->flags & ZER && pfinfo->flags & HTG && (IS_X(pfinfo->spec)
					|| pfinfo->spec == 'p' || pfinfo->spec == 'b')))
		pf_pad_handle(pfinfo, str);
	pf_x_toupper(*str, pfinfo->spec);
}

void		pf_alt_handle(t_info *pfinfo, char **str)
{
	char	*newstr;

	if (!(ISXO(pfinfo->spec) || pfinfo->spec == 'p' || pfinfo->spec == 'b'))
		return ;
	newstr = ft_strdup(*str);
	if (pfinfo->spec == 'p')
		pf_insert_to_str(&newstr, "0x");
	else if (pfinfo->flags & HTG)
	{
		if (pfinfo->spec == 'b' && ft_strcmp("0", *str) &&
				ft_strcmp("\0", *str))
			pf_insert_to_str(&newstr, "0b");
		else if (IS_X(pfinfo->spec) && ft_strcmp("0", *str) &&
				ft_strcmp("\0", *str))
			pf_insert_to_str(&newstr, "0x");
		else if (IS_O(pfinfo->spec) && **str != '0')
			pf_insert_to_str(&newstr, "0");
	}
	free(*str);
	*str = newstr;
}

void		pf_x_toupper(char *str, char spec)
{
	if (spec != 'X')
		return ;
	while (*str)
	{
		if (ft_isalpha(*str))
			*str = ft_toupper(*str);
		str++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:55:09 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:45:19 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	pf_int_len(char length, va_list arg)
{
	if (length == hh)
		return ((signed char)va_arg(arg, int));
	if (length == h)
		return ((short)va_arg(arg, int));
	if (length == l)
		return (va_arg(arg, long));
	if (length == ll)
		return (va_arg(arg, long long));
	if (length == j)
		return (va_arg(arg, intmax_t));
	if (length == z)
		return (va_arg(arg, ssize_t));
	return (va_arg(arg, int));
}

void		pf_conv_num(t_vector *vector, t_info *pfinfo, va_list arg)
{
	intmax_t	ival;
	char		*str;

	if (pfinfo->spec == 'D')
		pfinfo->length = l;
	if (pfinfo->spec == 'i' || pfinfo->spec == 'D')
		pfinfo->spec = 'd';
	ival = pf_int_len(pfinfo->length, arg);
	str = pf_imaxtoa(ival);
	if (pfinfo->prec != -1 && pfinfo->flags & ZER)
		pfinfo->flags ^= ZER;
	if (pfinfo->prec == 0 && !ft_strcmp("0", str))
		*str = '\0';
	if (((pfinfo->flags & POS || pfinfo->flags & INV) && str[0] != '-')
			&& pfinfo->spec == 'd')
	{
		pf_insert_to_str(&str, (pfinfo->flags & INV) ? " " : "+");
		str[0] = ((pfinfo->flags & POS)) ? '+' : str[0];
	}
	pf_prec_nums(pfinfo, &str);
	pf_pad_handle(pfinfo, &str);
	pf_vector_push(vector, str);
	free(str);
}

void		pf_conv_octal(t_vector *vector, t_info *pfinfo, va_list arg)
{
	uintmax_t	oct;
	char		*str;

	if (pfinfo->spec == 'O')
		pfinfo->length = l;
	oct = pf_xou_len(pfinfo->length, arg);
	str = pf_uimaxtoa_base(oct, 8, "01234567");
	pf_xou_handle(&str, pfinfo);
	pf_vector_push(vector, str);
	free(str);
}

void		pf_conv_hex(t_vector *vector, t_info *pfinfo, va_list arg)
{
	uintmax_t	hex;
	char		*str;

	if (pfinfo->spec == 'p')
		pfinfo->length = j;
	hex = pf_xou_len(pfinfo->length, arg);
	str = pf_uimaxtoa_base(hex, 16, "0123456789abcdef");
	if (pfinfo->spec == 'p' && pfinfo->flags & ZER && pfinfo->pset)
		pfinfo->flags ^= ZER;
	pf_xou_handle(&str, pfinfo);
	pf_vector_push(vector, str);
	free(str);
}

void		pf_conv_uns(t_vector *vector, t_info *pfinfo, va_list arg)
{
	uintmax_t	uns;
	char		*str;

	if (pfinfo->spec == 'U')
		pfinfo->length = l;
	uns = pf_xou_len(pfinfo->length, arg);
	str = pf_uimaxtoa_base(uns, 10, "0123456789");
	pf_xou_handle(&str, pfinfo);
	pf_vector_push(vector, str);
	free(str);
}

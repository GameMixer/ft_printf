/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:18:42 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:45:53 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_null_str(t_info *pfinfo)
{
	char	*temp;

	if (pfinfo->prec >= 1 || pfinfo->prec == -1)
	{
		temp = ft_strdup("(null)");
		if (pfinfo->prec > 6)
			temp[6] = '\0';
		else
			temp[(pfinfo->prec == -1) ? 6 : pfinfo->prec] = '\0';
	}
	else
		temp = ft_strdup("");
	return (temp);
}

void	pf_conv_str(t_vector *vector, t_info *pfinfo, va_list arg)
{
	char	*temp;
	char	*str;

	if (pfinfo->length == l)
	{
		pf_conv_wstr(vector, pfinfo, arg);
		return ;
	}
	temp = va_arg(arg, char *);
	if (!temp)
		str = pf_null_str(pfinfo);
	else
		str = ft_strdup(temp);
	pf_prec_handle(pfinfo, &str);
	pf_pad_handle(pfinfo, &str);
	pf_vector_push(vector, str);
	free(str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spec_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:50:04 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 20:44:09 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_cspec	g_convert[] =
{
	{'d', &pf_conv_num},
	{'D', &pf_conv_num},
	{'i', &pf_conv_num},
	{'p', &pf_conv_hex},
	{'o', &pf_conv_octal},
	{'O', &pf_conv_octal},
	{'x', &pf_conv_hex},
	{'X', &pf_conv_hex},
	{'u', &pf_conv_uns},
	{'U', &pf_conv_uns},
	{'s', &pf_conv_str},
	{'S', &pf_conv_wstr},
	{'c', &pf_conv_char},
	{'C', &pf_conv_char},
	{'b', &pf_conv_binary},
	{'f', &pf_conv_float},
	{'n', &pf_conv_none},
	{'%', &pf_conv_percent}
};

void	pf_get_conv(t_vector *vector, t_info *pfinfo, va_list arg)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	while (i < SPECS)
	{
		if (pfinfo->spec == g_convert[i].spec)
		{
			g_convert[i].ptr(vector, pfinfo, arg);
			flag = 0;
		}
		i++;
	}
	if (flag)
		pf_conv_percent(vector, pfinfo, arg);
}

void	pf_handle_spec(t_vector *vector, const char **format,
		t_info *pfinfo, va_list arg)
{
	if (**format == '{')
		if (pf_colors(vector, format) == 1)
			return ;
	while (1)
	{
		if (pf_check_flags(format, pfinfo))
			continue ;
		if (pf_check_width(format, pfinfo, arg))
			continue ;
		if (pf_check_prec(format, pfinfo, arg))
			continue ;
		if (pf_check_len(format, pfinfo))
			continue ;
		if (**format == '\0')
			return ;
		pfinfo->spec = *(*format)++;
		break ;
	}
	pf_get_conv(vector, pfinfo, arg);
}

int		pf_strprintf(char **ret, const char *format, va_list arg)
{
	size_t		i;
	t_vector	vector;
	t_info		pfinfo;

	pf_info_init(&pfinfo);
	if (pf_vector_init(&vector, ft_strlen(format) + 50) == -1)
		return (-1);
	while (*format)
	{
		i = 0;
		while (format[i] && format[i] != '%')
			i++;
		pf_vector_npush(&vector, (char *)format, i);
		format += i;
		if (*format == '%')
		{
			if (*(++format) == 0)
				break ;
			pf_handle_spec(&vector, &format, &pfinfo, arg);
		}
		pf_info_init(&pfinfo);
	}
	*ret = ft_strndup(vector.data, vector.len);
	pf_vector_clear(&vector);
	return (vector.len);
}

void	pf_info_init(t_info *pfinfo)
{
	pfinfo->width = 0;
	pfinfo->prec = -1;
	pfinfo->spec = 'N';
	pfinfo->flags = 0;
	pfinfo->length = -1;
	pfinfo->pset = 0;
}

void	pf_conv_percent(t_vector *vector, t_info *pfinfo, va_list arg)
{
	char	*str;

	(void)arg;
	str = ft_strnew(1);
	*str = pfinfo->spec;
	pf_pad_handle(pfinfo, &str);
	pf_vector_push(vector, str);
	free(str);
}

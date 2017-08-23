/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:50:05 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/08 20:41:47 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		g_colors[33][2][15] = {
	{"{red}", "\033[31m"},
	{"{bred}", "\033[31;1m"},
	{"{green}", "\033[32m"},
	{"{bgreen}", "\033[32;1m"},
	{"{yellow}", "\033[33m"},
	{"{byellow}", "\033[33;1m"},
	{"{blue}", "\033[34m"},
	{"{bblue}", "\033[34;1m"},
	{"{purple}", "\033[35m"},
	{"{bpurple}", "\033[35;1m"},
	{"{cyan}", "\033[36m"},
	{"{bcyan}", "\033[36;1m"},
	{"{black}", "\033[30m"},
	{"{bblack}", "\033[30;1m"},
	{"{white}", "\033[37m"},
	{"{bwhite}", "\033[37;1m"},
	{"{b_red}", "\033[41m"},
	{"{b_bred}", "\033[41;1m"},
	{"{b_green}", "\033[42m"},
	{"{b_bgreen}", "\033[42;1m"},
	{"{b_yellow}", "\033[43m"},
	{"{b_byellow}", "\033[43;1m"},
	{"{b_blue}", "\033[44m"},
	{"{b_bblue}", "\033[44;1m"},
	{"{b_purple}", "\033[45m"},
	{"{b_bpurple}", "\033[45;1m"},
	{"{b_cyan}", "\033[46m"},
	{"{b_bcyan}", "\033[46;1m"},
	{"{b_black}", "\033[40m"},
	{"{b_bblack}", "\033[40;1m"},
	{"{b_white}", "\033[47m"},
	{"{b_bwhite}", "\033[47;1m"},
	{"{eoc}", "\033[0m"}
};

int			pf_colors(t_vector *vector, const char **format)
{
	int		i;

	i = 0;
	while (i < 33)
	{
		if (ft_strnstr(*format, g_colors[i][0], ft_strlen(g_colors[i][0])) != 0)
		{
			pf_vector_push(vector, g_colors[i][1]);
			*format = *format + ft_strlen(g_colors[i][0]);
			return (1);
		}
		i++;
	}
	return (0);
}

void		pf_conv_binary(t_vector *vector, t_info *pfinfo, va_list arg)
{
	uintmax_t	binary;
	char		*str;

	binary = va_arg(arg, unsigned long long);
	str = pf_uimaxtoa_base(binary, 2, "01");
	pf_xou_handle(&str, pfinfo);
	pf_vector_push(vector, str);
	free(str);
}

void		pf_conv_none(t_vector *vector, t_info *pfinfo, va_list arg)
{
	intmax_t	*i;
	int			temp;

	temp = vector->len;
	i = pf_none_len(pfinfo, arg);
	*i = (intmax_t)temp;
}

intmax_t	*pf_none_len(t_info *pfinfo, va_list arg)
{
	if (pfinfo->length == hh)
		return ((intmax_t *)va_arg(arg, signed char *));
	if (pfinfo->length == h)
		return ((intmax_t *)va_arg(arg, short *));
	if (pfinfo->length == l)
		return ((intmax_t *)va_arg(arg, long *));
	if (pfinfo->length == ll)
		return ((intmax_t *)va_arg(arg, long long *));
	if (pfinfo->length == j)
		return ((intmax_t *)va_arg(arg, intmax_t *));
	if (pfinfo->length == z)
		return ((intmax_t *)va_arg(arg, ssize_t *));
	return ((intmax_t *)va_arg(arg, int *));
}

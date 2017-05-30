/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 15:35:15 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 19:27:13 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_buff_set(void)
{
	int		n;

	n = 0;
	while (n < PRINTF_BUFF)
	{
		g_buff[n] = '\0';
		n++;
	}
	g_i = 0;
}

void	pf_buff_display(t_flag *f)
{
	f->ret += write(1, g_buff, g_i);
	pf_buff_set();
}

void	pf_buff_null(t_flag *f)
{
	static char	str[6] = "(null)";
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		pf_buff(str[i], f);
		i++;
	}
}

void	pf_buff(char c, t_flag *f)
{
	g_buff[g_i] = c;
	g_i++;
	if (g_i == PRINTF_BUFF)
		pf_buff_display(f);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:46:20 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 19:46:43 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_check(t_flag *f)
{
	pf_initialize(f);
	while (f->frmt[f->index] == '#' || f->frmt[f->index] == '0'
			|| f->frmt[f->index] == '-' || f->frmt[f->index] == '+'
			|| f->frmt[f->index] == ' ' || f->frmt[f->index] == 'h'
			|| f->frmt[f->index] == 'l' || f->frmt[f->index] == 'j'
			|| f->frmt[f->index] == 'z' || f->frmt[f->index] == '.'
			|| ft_isdigit(f->frmt[f->index]))
	{
		pf_check_flag(f);
		pf_check_width(f);
		pf_check_precision(f);
		pf_check_modifier(f);
	}
	if (f->index == (int)ft_strlen(f->frmt))
		return (-1);
	return (0);
}

void	pf_check_flag(t_flag *f)
{
	if (f->frmt[f->index] == '#' || f->frmt[f->index] == '0'
			|| f->frmt[f->index] == '-' || f->frmt[f->index] == '+'
			|| f->frmt[f->index] == ' ')
	{
		if (f->frmt[f->index] == '#')
			f->type[2] = 1;
		if (f->frmt[f->index] == '0')
			f->type[3] = 1;
		if (f->frmt[f->index] == '-')
			f->type[4] = 1;
		if (f->frmt[f->index] == '+')
			f->type[5] = 1;
		if (f->frmt[f->index] == ' ')
			f->type[6] = 1;
		f->index++;
	}
}

void	pf_check_width(t_flag *f)
{
	int		i;
	char	*str;

	i = f->index;
	if (ft_isdigit(f->frmt[f->index]) && f->frmt[f->index] != '0')
	{
		while (ft_isdigit(f->frmt[f->index]))
			f->index++;
		if (f->index - i > 0)
		{
			f->type[1] = 0;
			str = ft_strsub(f->frmt, i, f->index - i);
			f->type[1] = ft_atoi((const char *)str);
			free(str);
		}
	}
}

void	pf_check_precision(t_flag *f)
{
	int		i;
	char	*str;

	if (f->frmt[f->index] == '.')
	{
		f->type[0] = 0;
		i = (f->index) + 1;
		while (ft_isdigit(f->frmt[f->index]))
			f->index++;
		if (f->index - i > 0)
		{
			str = ft_strsub(f->frmt, i, f->index - i);
			f->type[0] = ft_atoi((const char *)str);
			free(str);
		}
		if (f->type[0] == 0)
			f->type[0] = -1;
	}
}

void	pf_check_modifier(t_flag *f)
{
	while (f->frmt[f->index] == 'h' || f->frmt[f->index] == 'l' ||
			f->frmt[f->index] == 'j' || f->frmt[f->index] == 'z')
	{
		if (f->frmt[f->index] == 'h' && f->frmt[f->index + 1] == 'h')
		{
			f->type[7] = 1;
			f->index++;
		}
		else if (f->frmt[f->index] == 'h')
			f->type[8] = 1;
		if (f->frmt[f->index] == 'l' && f->frmt[f->index + 1] == 'l')
		{
			f->type[9] = 1;
			f->index++;
		}
		else if (f->frmt[f->index] == 'l')
			f->type[10] = 1;
		if (f->frmt[f->index] == 'j')
			f->type[11] = 1;
		if (f->frmt[f->index] == 'z')
			f->type[12] = 1;
		f->index++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 17:46:20 by gderenzi          #+#    #+#             */
/*   Updated: 2017/04/17 18:00:25 by gderenzi         ###   ########.fr       */
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
		
	}
	if (f->index == ft_strlen(f->frmt))
		return (-1);
	return (0);
}



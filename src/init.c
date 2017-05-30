/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:00:39 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/25 19:45:17 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_init_specs_p2(t_spec *specs)
{
	specs[11].c = 'x';
	specs[11].ptr = &pf_handler_x;
	specs[12].c = 'X';
	specs[12].ptr = &pf_handler_wx;
	specs[13].c = 'p';
	specs[13].ptr = &pf_handler_p;
	specs[14].c = 0;
	specs[14].ptr = NULL;
}

void	pf_init_specs(t_spec *specs)
{
	specs[0].c = 's';
	specs[0].ptr = &pf_handler_s;
	specs[1].c = 'S';
	specs[1].ptr = &pf_handler_ws;
	specs[2].c = 'c';
	specs[2].ptr = &pf_handler_c;
	specs[3].c = 'C';
	specs[3].ptr = &pf_handler_wc;
	specs[4].c = 'd';
	specs[4].ptr = &pf_handler_d;
	specs[5].c = 'D';
	specs[5].ptr = &pf_handler_wd;
	specs[6].c = 'i';
	specs[6].ptr = &pf_handler_d;
	specs[7].c = 'o';
	specs[7].ptr = &pf_handler_o;
	specs[8].c = 'O';
	specs[8].ptr = &pf_handler_wo;
	specs[9].c = 'u';
	specs[9].ptr = &pf_handler_u;
	specs[10].c = 'U';
	specs[10].ptr = &pf_handler_wu;
	pf_init_specs_p2(specs);
}

void	pf_initialize(t_flag *f)
{
	int	i;

	i = 0;
	while (i < 14)
	{
		f->type[i] = 0;
		i++;
	}
	f->index = 0;
}

int		pf_init_validate(t_flag *f, va_list *args)
{
	t_spec	specs[16];
	int		j;

	if (pf_check(f) == -1)
		return (-1);
	pf_init_specs(specs);
	f->arg = NULL;
	f->warg = NULL;
	j = 0;
	f->spec = f->frmt[f->index];
	while (specs[j].c != f->spec && specs[j].c != 0)
		j++;
	if (specs[j].c == 0)
		return (pf_handler_undefined(f));
	return (specs[j].ptr(f, args));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 18:00:39 by gderenzi          #+#    #+#             */
/*   Updated: 2017/04/17 18:10:03 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
}

void	pf_initialize(t_flags *f)
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

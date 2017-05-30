/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 18:02:06 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 11:17:11 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_precision_string(t_flag *f)
{
	if (f->type[0] == -1)
		f->arg = "\0";
	else if (f->spec == 'S' || (f->spec == 's' && f->type[10] == 1))
		f->arg = pf_wstrsub(f->warg, 0, f->type[0]);
	else if (f->spec == 's')
		f->arg = pf_wstrsub(f->warg, 0, f->type[0]);
}

void	pf_sharp(t_flag *f)
{
	if ((f->type[2] == 1 && f->arg[0] != '0' && f->type[0] != -1)
			|| f->spec == 'p')
	{
		if (f->spec == 'o' || f->spec == 'O' || f->spec == 'x'
				|| f->spec == 'X' || f->spec == 'p')
		{
			if ((f->spec == 'x' && f->arg[0] != '0') || f->spec == 'p')
			{
				pf_buff('0', f);
				pf_buff('x', f);
			}
			else if (f->spec == 'X' && f->arg[0] != '0')
			{
				pf_buff('0', f);
				pf_buff('X', f);
			}
			else if ((f->spec == 'o' || f->spec == 'O') &&
					f->type[0] <= (int)ft_strlen(f->arg))
				pf_buff('0', f);
			else if ((f->spec == 'o' || f->spec == 'O') && f->type[0] == -1)
				pf_buff('0', f);
		}
	}
}

void	pf_space_plus_sharp(t_flag *f)
{
	if (f->type[5] == 1 || f->type[6] == 1)
	{
		if (f->spec == 'd' || f->spec == 'D' || f->spec == 'i')
		{
			if (f->type[6] == 1 && f->type[5] == 0 && f->sign != '-')
				pf_buff(' ', f);
			if (f->type[5] == 1 && ft_isdigit(f->arg[0]) && f->sign == '+')
				pf_buff('+', f);
		}
	}
	if (f->sign == '-')
		pf_buff('-', f);
	pf_sharp(f);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:50:04 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/18 18:16:13 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_apply_mask(t_flag *f, int *mask)
{
	int	i;

	i = 2;
	while (i < 14)
	{
		f->type[i] = f->type[i] * mask[i];
		i++;
	}
}

int		pf_handler_char(t_flag *f)
{
	if (f->type[0] != 0 && (f->spec != 'C' ||
				(f->spec == 'c' && f->type[10] == 1)))
		pf_precision_string(f);
	else if (f->spec == 'S' || (f->spec == 's' && f->type[10] == 1) ||
			f->spec == 'C' || (f->spec == 'c' && f->type[10] == 1))
		f->arg = pf_wchar_to_char(f->warg);
	if (f->type[1] > 0)
		pf_width_char(f);
	if (f->type[1] == 0)
		pf_display_arg(f);
	return (1);
}

int		pf_handler_num(t_flag *f)
{
	int	i;

	i = -1;
	if (f->type[0] == -1 && f->arg[0] == '0' && !(f->type[2] == 1 &&
				(f->spec == 'o' || f->spec == 'O' || f->spec == 'p')))
		f->arg = "\0";
	if (f->type[1] > 0)
		pf_width_num(f);
	else if (f->type[1] == 0 && f->type[0] > 0)
		pf_precision_without_width(f);
	if (f->type[0] <= 0 && f->type[1] == 0)
		pf_space_plus_sharp(f);
	while (f->arg[++i] != '\0' && f->type[1] == 0)
		pf_buff(f->arg[i], f);
	pf_end(f);
	return (1);
}

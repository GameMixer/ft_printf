/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:55:09 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 11:13:03 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_precision_without_width(t_flag *f)
{
	int	len;
	int	prec;

	prec = f->type[0];
	len = ft_strlen(f->arg);
	pf_space_plus_sharp(f);
	while (prec > len-- && len > 0)
		prec--;
	if (f->type[0] > f->type[1] + (int)ft_strlen(f->arg))
	{
		while (++len < prec)
			pf_buff('0', f);
	}
}

void	pf_precision_num(t_flag *f, int len_zero)
{
	int	len;

	len = ft_strlen(f->arg);
	if (f->type[5] == 1 || f->type[6] == 1 || f->sign == '-' || (f->type[2] == 1
				&& f->type[0] <= len && (f->spec == 'o' || f->spec == 'O')))
		len_zero--;
	if (f->type[2] == 1 && (f->spec == 'x' || f->spec == 'X' || f->spec == 'p'))
		len_zero = len_zero - 2;
	while (f->type[0] > len++)
		len_zero--;
	if (f->type[0] < f->type[1] + (int)ft_strlen(f->arg))
	{
		while (len_zero-- > 0)
		{
			if (f->type[3] == 1 && f->type[0] == 0)
				pf_buff('0', f);
			else
				pf_buff(' ', f);
		}
	}
}

void	pf_zero_num(t_flag *f)
{
	int	i;
	int	len;
	int	len_zero;

	i = -1;
	len = ft_strlen(f->arg);
	len_zero = f->type[1] - len;
	if (f->type[3] == 1)
	{
		pf_space_plus_sharp(f);
		pf_precision_num(f, len_zero);
	}
	else
	{
		pf_precision_num(f, len_zero);
		pf_space_plus_sharp(f);
	}
	while (f->type[0] > len++)
		pf_buff('0', f);
	while (f->arg[++i] != '\0')
		pf_buff(f->arg[i], f);
}

void	pf_minus_num(t_flag *f)
{
	int	i;
	int	len;
	int	len_zero;

	i = -1;
	len_zero = f->type[1] - ft_strlen(f->arg);
	len = ft_strlen(f->arg);
	f->type[3] = 0;
	pf_space_plus_sharp(f);
	while (f->type[0] > len++)
		pf_buff('0', f);
	while (f->arg[++i] != '\0')
		pf_buff(f->arg[i], f);
	pf_precision_num(f, len_zero);
}

void	pf_width_num(t_flag *f)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(f->arg);
	if (len < f->type[1])
	{
		if (f->type[4] == 1)
			pf_minus_num(f);
		else
			pf_zero_num(f);
	}
	else
	{
		pf_space_plus_sharp(f);
		while (f->type[0] > len++)
			pf_buff('0', f);
		while (f->arg[++i] != '\0')
			pf_buff(f->arg[i], f);
	}
}

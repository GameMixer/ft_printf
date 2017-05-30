/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:42:33 by gderenzi          #+#    #+#             */
/*   Updated: 2017/05/30 13:07:07 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_display_arg(t_flag *f)
{
	int		i;
	size_t	len;

	i = -1;
	if ((f->spec == 's' && f->type[10] == 1) || f->spec == 'S' ||
				(f->spec == 'c' && f->type[10] == 1) || f->spec == 'C')
	{
		if (f->arg != NULL)
		{
			if (f->arg[0] == '\0' && (f->spec == 'C' ||
						(f->spec == 'c' && f->type[10] == 1)))
				pf_buff('\0', f);
			len = ft_strlen(f->arg);
			while (len-- > 0)
				pf_buff(f->arg[++i], f);
		}
		else if (f->type[0] != -1)
			pf_buff_null(f);
	}
	else
		while (f->arg[++i] != '\0')
			pf_buff(f->arg[i], f);
	pf_end(f);
}

void	pf_zero_char(t_flag *f)
{
	int	nb_space;

	nb_space = f->type[1] - ft_strlen(f->arg);
	if ((f->spec == 'c' && f->arg[0] == 0) ||
			(f->spec == 'C' && f->arg[0] == 0))
		nb_space--;
	while (nb_space-- > 0)
	{
		if (f->type[3] == 1 && f->type[0] <= 0)
			pf_buff('0', f);
		else
			pf_buff(' ', f);
	}
	pf_display_arg(f);
}

void	pf_minus_char(t_flag *f)
{
	int	nb_space;

	nb_space = f->type[1] - ft_strlen(f->arg);
	if ((f->spec == 'c' && f->arg[0] == 0) ||
			(f->spec == 'C' && f->arg[0] == 0))
		nb_space--;
	pf_display_arg(f);
	while (nb_space-- > 0)
		pf_buff(' ', f);
}

void	pf_width_char(t_flag *f)
{
	int	i;

	i = 0;
	if (f->arg)
		i = ft_strlen(f->arg);
	if (i < f->type[1])
	{
		if (f->type[4] == 1)
			pf_minus_char(f);
		else
			pf_zero_char(f);
	}
	else
		pf_display_arg(f);
}

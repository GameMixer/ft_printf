/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 11:22:11 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/07 20:31:45 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_prec_nums(t_info *pfinfo, char **str)
{
	char	*new;
	char	extra;
	char	*orig;

	orig = *str;
	if (pfinfo->prec == 0 && !ft_strcmp("0", *str))
	{
		**str = '\0';
		return ;
	}
	if (pfinfo->prec == -1)
		pfinfo->prec = 1;
	if ((size_t)pfinfo->prec < ft_strlen(*str))
		return ;
	extra = (!ft_isdigit((*str)[0]) && pfinfo->spec == 'd') ? (*str)[0] : 0;
	if (extra)
		(*str)++;
	new = ft_strnew(pfinfo->prec + (extra != 0));
	ft_memset(new + (extra != 0), '0', pfinfo->prec - ft_strlen(*str));
	ft_strcpy(new + pfinfo->prec - ft_strlen(*str) + (extra != 0), *str);
	if (extra)
		new[0] = extra;
	free(orig);
	*str = new;
}

void	pf_prec_handle(t_info *pfinfo, char **str)
{
	if (pfinfo->prec != -1 && ft_strlen(*str) > (size_t)pfinfo->prec)
		(*str)[pfinfo->prec] = '\0';
}

void	pf_prec_right(t_info *pfinfo, char **str, char *newstr)
{
	char	extra;

	extra = 0;
	if (pfinfo->flags & ZER)
	{
		extra = (!ft_isdigit((*str)[0]) && pfinfo->spec == 'd') ? (*str)[0] : 0;
		ft_memset(newstr, '0', pfinfo->width - ft_strlen(*str) + (extra != 0));
		if (extra)
		{
			newstr[0] = extra;
			(*str)[0] = '0';
		}
	}
	else
	{
		ft_memset(newstr, ' ', pfinfo->width - ft_strlen(*str));
		if ((pfinfo->flags & POS) && **str != '-')
			newstr[pfinfo->width - ft_strlen(*str)] =
				((*str)[0] == '-') ? '-' : '+';
	}
	ft_strcpy(newstr + pfinfo->width - ft_strlen(*str)
			+ (extra != 0), *str + (extra != 0));
}

void	pf_pad_handle(t_info *pfinfo, char **str)
{
	char	*new;

	if (pfinfo->width != 0 && ft_strlen(*str) < (size_t)pfinfo->width)
	{
		new = ft_strnew(pfinfo->width);
		if (pfinfo->flags & LFT)
		{
			ft_strcpy(new, *str);
			ft_memset(new + ft_strlen(*str), ' ',
					pfinfo->width - ft_strlen(*str));
		}
		else
			pf_prec_right(pfinfo, str, new);
		free(*str);
		*str = new;
	}
}

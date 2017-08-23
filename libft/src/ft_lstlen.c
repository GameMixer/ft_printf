/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 15:24:46 by gderenzi          #+#    #+#             */
/*   Updated: 2017/07/06 15:26:57 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstlen(t_list *lst)
{
	int		i;
	t_list	*list;

	i = 0;
	if (lst)
	{
		list = lst;
		while (list)
		{
			i++;
			list = list->next;
		}
	}
	return (i);
}

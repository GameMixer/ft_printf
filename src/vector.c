/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 11:59:18 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/02 16:54:42 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		pf_vector_init(t_vector *vector, size_t cap)
{
	if (!vector || !cap)
		return (-1);
	vector->len = 0;
	vector->cap = cap;
	if ((vector->data = ft_memalloc(sizeof(char) * vector->cap)) == NULL)
		return (-1);
	return (0);
}

void	pf_vector_push(t_vector *vector, char *data)
{
	size_t	len;

	len = ft_strlen(data);
	if (vector->cap < vector->len + len)
		pf_vector_resize(vector, vector->len + len);
	ft_memcpy(vector->data + vector->len, data, len);
	vector->len += len;
}

void	pf_vector_npush(t_vector *vector, char *data, size_t n)
{
	size_t	len;

	len = n;
	if (vector->cap < vector->len + len)
		pf_vector_resize(vector, vector->len + len);
	ft_memcpy(vector->data + vector->len, data, len);
	vector->len += len;
}

void	pf_vector_resize(t_vector *vector, size_t min)
{
	size_t	size;

	if (!(vector->data))
		pf_vector_init(vector, min);
	size = vector->cap;
	while (size < min)
		size *= 2;
	vector->data = (char *)pf_realloc(vector->data, vector->len, size);
	vector->cap = size;
}

void	pf_vector_clear(t_vector *vector)
{
	if (vector->data && vector->cap > 0)
	{
		free(vector->data);
		vector->data = NULL;
	}
}

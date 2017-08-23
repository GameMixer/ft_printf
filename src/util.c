/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gderenzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 16:28:40 by gderenzi          #+#    #+#             */
/*   Updated: 2017/08/07 20:57:07 by gderenzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	pf_findchar(const char *s, int c)
{
	int				i;
	unsigned char	a;

	a = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == a)
			return (i);
		i++;
	}
	if (s[i] == a)
		return (ft_strlen(s) + 1);
	return (0);
}

void	*pf_realloc(void *ptr, size_t src_size, size_t new_size)
{
	void	*new_ptr;

	if (!new_size)
	{
		if (ptr)
			free(ptr);
		return (ptr);
	}
	if (!ptr)
		return (ft_memalloc(new_size));
	if (new_size <= src_size)
		return (ptr);
	new_ptr = ft_memalloc(new_size);
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, src_size);
		free(ptr);
	}
	return (new_ptr);
}

char	*pf_imaxtoa(intmax_t value)
{
	uintmax_t	i;
	intmax_t	size;
	char		*ret;

	i = (value < 0) ? -value : value;
	size = 1 + (value < 0);
	while ((i /= 10))
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = (value < 0) ? -value : value;
	ret[--size] = "0123456789"[i % 10];
	while ((i /= 10))
		ret[--size] = "0123456789"[i % 10];
	if (value < 0)
		ret[--size] = '-';
	return (ret);
}

char	*pf_uimaxtoa_base(uintmax_t value, int base, const char *str)
{
	uintmax_t	i;
	size_t		size;
	char		*ret;

	i = value;
	size = 1;
	while ((i /= base))
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = '\0';
	i = value;
	ret[--size] = str[i % base];
	while ((i /= base))
		ret[--size] = str[i % base];
	return (ret);
}

void	pf_insert_to_str(char **s1, char *s2)
{
	char	*str;
	char	*strcpy;
	char	*newstr;

	if (s1 && s2)
	{
		newstr = ft_strnew(ft_strlen(*s1) + ft_strlen(s2) + 1);
		str = newstr;
		strcpy = *s1;
		while (*s2)
			*str++ = *s2++;
		while (*strcpy)
			*str++ = *strcpy++;
		*str = '\0';
		free(*s1);
		*s1 = newstr;
	}
}
